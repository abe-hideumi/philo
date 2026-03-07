# CLAUDE.md

このファイルは、このリポジトリで作業する際に Claude Code (claude.ai/code) へガイダンスを提供します。

## プロジェクト概要

POSIXスレッドとミューテックスを使用したC言語による「食事する哲学者問題」の実装です。このシミュレーションは、隣接する哲学者同士でフォーク（ミューテックス）を共有しながら、思考・食事・睡眠を繰り返す哲学者をモデル化しています。

## ビルドと実行

```bash
# プロジェクトをビルド
make

# オブジェクトファイルをクリーン
make clean

# すべてのビルド成果物をクリーン
make fclean

# 最初から再ビルド
make re

# プログラムを実行
./philo [num_philos] [time_to_die] [time_to_eat] [time_to_sleep] [optional: count_must_eat]
# 例: ./philo 5 800 200 200 7
```

引数:
- `num_philos`: 哲学者の数（フォークの数も同じ）
- `time_to_die`: 哲学者が餓死するまでの時間（ミリ秒）
- `time_to_eat`: 食事にかかる時間（ミリ秒）
- `time_to_sleep`: 睡眠時間（ミリ秒）
- `count_must_eat` (オプション): シミュレーション終了までに各哲学者が食事する回数

## アーキテクチャ

### データ構造

プログラムは3つの主要な構造体を使用します:

1. **t_params**: コマンドライン引数からのシミュレーションパラメータを格納
2. **t_data**: 以下を含む中央データ構造:
   - `start_time`: シミュレーション開始時刻
   - `someone_died`: 哲学者が死亡したかを示すフラグ
   - `print_mutex`: コンソール出力を同期化
   - `died_mutex`: `someone_died`フラグを保護
   - フォークと哲学者の配列
3. **t_philo**: 個々の哲学者の状態:
   - スレッドハンドル、ID、食事回数、最後の食事時刻
   - 左右のフォーク（ミューテックス）へのポインタ
   - `eat_mutex`: 哲学者の食事状態を保護
   - 共有データへの逆ポインタ

### プログラムフロー

実行は以下の順序で進行します:

1. **main.c**: エントリーポイント、引数の数を検証（5または6個必要）
2. **all_init()** ([src/init.c](src/init.c)): 3段階の初期化
   - `param_init()`: [utils/param_check.c](utils/param_check.c)と[utils/ft_atoi.c](utils/ft_atoi.c)を使用して引数を検証・パース
   - `data_init()`: フォークと哲学者のメモリを割り当て
   - `mutex_init()`: すべてのミューテックスを初期化し、フォークポインタを割り当て（フォーク共有のための循環割り当て）
3. **thread_create()** ([src/thread_create.c](src/thread_create.c)): `philo_routine`で哲学者スレッドを作成し、すべてのスレッドをjoin
4. **philo_routine()** ([src/philos_routine.c](src/philos_routine.c)): 哲学者のメインライフサイクル（現在未完成）
5. **cleanup()** ([utils/cleanup.c](utils/cleanup.c)): すべてのミューテックスを破棄し、割り当てられたメモリを解放

### フォーク割り当てパターン

各哲学者には2つのフォークが循環的に割り当てられます:
- 左フォーク: `data->forks[i]`
- 右フォーク: `data->forks[(i + 1) % num_philos]`

これにより、隣接する哲学者が正しくフォークを共有できます。

### タイミング

時間は`gettimeofday()`を使用してミリ秒単位で追跡されます:
- [src/times.c](src/times.c)は`time_in_ms()`でタイムスタンプを生成
- 各哲学者は`last_eat_time`を追跡して餓死を検出

### スレッド同期

シミュレーションは複数のミューテックスを使用します:
- フォークごとのミューテックス: フォークへのアクセスを制御
- 哲学者ごとの`eat_mutex`: 食事状態の更新を保護
- グローバル`print_mutex`: アトミックなコンソール出力を保証
- グローバル`died_mutex`: 死亡フラグのチェックを保護

## 開発メモ

- プロジェクトは42スクールのヘッダーフォーマットを使用（すべてのソースファイルで確認可能）
- エラーハンドリングは[utils/error.c](utils/error.c)の`error_exit()`でコード-1で終了
- `ft_atoi()`は正の数のみ受け付け（負の数を拒否、INT_MAX制限を強制）
- パラメータ検証には数字チェックと長さ制限が含まれる（最大10桁）
- 偶数番号の哲学者は開始時に100μs スリープしてデッドロックを防止
- [src/philos_routine.c](src/philos_routine.c)は現在未完成（スタブ実装）

## コード構成

```
philo/
├── main.c              # エントリーポイント
├── philo.h             # すべての構造体定義と関数プロトタイプ
├── src/
│   ├── init.c          # 初期化ロジック
│   ├── thread_create.c # スレッド管理
│   ├── philos_routine.c # 哲学者の振る舞い（未完成）
│   └── times.c         # タイミングユーティリティ
└── utils/
    ├── ft_atoi.c       # 文字列から整数への変換
    ├── param_check.c   # 引数検証
    ├── error.c         # エラーハンドリング
    └── cleanup.c       # リソースクリーンアップ
```

## コンパイラ設定

プロジェクトは厳格なコンパイルフラグを使用:
- `-Wall -Wextra -Werror`: すべての警告を有効化し、エラーとして扱う
