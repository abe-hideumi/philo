# 包括的コードレビュー

## Critical: 死亡検出の根本的な欠陥

**問題: モニタースレッドがない** ([src/philos_routine.c:47-63](src/philos_routine.c#L47-L63))

哲学者が「自分の死」を自分でチェックする設計になっていますが、致命的な欠陥があります。

```c
while (is_died(philo->data) == false)
{
    if (time_in_ms() - get_last_eat(philo) >= time_to_die)
        return (set_died(philo->data, philo), NULL);  // ← ここで自己死亡チェック
    pthread_mutex_lock(&philo->left_fork->mutex);  // ← ここでブロック！！
    // ...
}
```

`pthread_mutex_lock` は割り込み不可能です。フォーク競合でここが `time_to_die` ms以上ブロックされると、死亡検出ができません。例えば `./philo 5 200 150 150` のような厳しいケースで顕著になります。

**正しい解決策:** 全哲学者の `last_eat_time` を監視するモニタースレッドを別途起動する。

---

## Critical: 複数の "died" 出力が起きうるレース条件

**場所:** [src/philos_actions.c:36-44](src/philos_actions.c#L36-L44)

```c
void set_died(t_data *data, t_philo *philo)
{
    pthread_mutex_lock(&data->died_mutex);
    data->someone_died = true;
    pthread_mutex_unlock(&data->died_mutex);    // ← ここでロック解放
    pthread_mutex_lock(&philo->data->print_mutex);
    printf("%lld %d died\n", ...);             // ← 複数スレッドが両方ここに到達しうる
    pthread_mutex_unlock(&philo->data->print_mutex);
}
```

哲学者AとBが同時に `set_died` を呼んだ場合:
1. A: `someone_died = true` → unlock
2. B: lock → `someone_died = true` → unlock
3. A と B 両方が `print_mutex` を競い、両方 "died" を出力

`print_mutex` を取る前に `someone_died` チェックが必要です。

---

## Bug: `ate_enough_count` インクリメントのアンロック後チェック

**場所:** [src/philos_actions.c:53-63](src/philos_actions.c#L53-L63)

```c
pthread_mutex_unlock(&philo->eat_mutex);
if (philo->eat_count == philo->data->params.count_must_eat)  // ← mutex外で読んでいる
{
    pthread_mutex_lock(&philo->data->died_mutex);
    philo->data->ate_enough_count++;
    // ...
}
```

`eat_count` を `eat_mutex` 解放後に読んでいます。このスレッドしか `eat_count` を書かないので現状は問題になりませんが、`ate_enough_count` へのアクセスも `died_mutex` だけで保護しており、`eat_count` の読み取りと一貫性がありません。

---

## Bug: `start_time` の同期なし書き込み ([src/thread_create.c:51](src/thread_create.c#L51))

```c
void thread_create_join(t_data *data)
{
    data->start_time = time_in_ms();  // ← メインスレッドが書く
    thread_create(data);              // ← 子スレッドがすぐ読む
    thread_join(data);
}
```

C11/POSIX のメモリモデル的には、`pthread_create` の前に `start_time` を書くので `pthread_create` 自体がメモリバリアになります。実用上は問題ありませんが、`start_time` は `thread_create` の前に設定しているため、スレッドが実際に動き始めるまでの遅延分だけ `start_time` が早い値になります。実際の問題は軽微ですが、意識しておくべきです。

---

## Minor: `print_status` の TOCTOU

**場所:** [src/philos_actions.c:16-24](src/philos_actions.c#L16-L24)

```c
void print_status(t_philo *philo, char *status)
{
    if (is_died(philo->data) == true)   // ← 1回目チェック
        return;
    pthread_mutex_lock(&philo->data->print_mutex);
    if (!is_died(philo->data))           // ← 2回目チェック（よい）
        printf(...);
    pthread_mutex_unlock(&philo->data->print_mutex);
}
```

1回目と2回目チェックの間に `someone_died` が変わりうる点は、2回目チェックで対処されており、これ自体は**良い実装**です。1回目は単純な早期リターン最適化なので問題ありません。

---

## Minor: `mutex_init` の部分クリーンアップのロジック

**場所:** [src/init_src.c:96-100](src/init_src.c#L96-L100)

```c
if (pthread_mutex_init(&data->philos[i].eat_mutex, NULL))
{
    pthread_mutex_destroy(&data->forks[i].mutex);  // ← iのforkを個別destroyしてから
    cleanup_partial(data, i);                       // ← cleanup_partialもiまでdestroyする
```

`cleanup_partial` は `must > 0` の間 `must--` してdestroyするため、インデックス `i` のフォークは `cleanup_partial(data, i)` でも destroy されます。上の `pthread_mutex_destroy(&data->forks[i].mutex)` と合わせて **二重destroy** になっています。

---

## 良い実装 (評価点)

- `ft_sleep` 内で `is_died` を 500μs ごとにチェックしており、sleep中の応答性は確保されている
- `one_philo_routine` で1人哲学者を特別処理しているのは正しい
- 偶数IDの哲学者を100μs 遅延させるデッドロック回避は適切
- `print_status` の二重チェックパターンは正しい
- `param_check` と `ft_atoi` の入力検証は堅牢

---

## 優先度まとめ

| 優先度 | 問題 | 場所 |
|--------|------|------|
| **Critical** | モニタースレッドなしでmutexブロック中の死亡未検出 | [philos_routine.c](src/philos_routine.c) |
| **Critical** | `set_died` で複数 "died" 出力 | [philos_actions.c:36](src/philos_actions.c#L36-L44) |
| **Bug** | `cleanup_partial` の二重 mutex_destroy | [init_src.c:98-99](src/init_src.c#L98-L99) |

最も根本的な問題はモニタースレッドの欠如で、これが修正できれば `set_died` の複数呼び出し問題も整理しやすくなります。
