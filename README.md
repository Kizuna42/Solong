# So_long - 42 School Project

2D ゲームプロジェクト：プレイヤーがマップ上の収集アイテムを全て集めて出口から脱出するゲーム

## 🎮 ゲーム概要

- **目標**: マップ上のすべての収集アイテム（C）を集め、出口（E）から脱出
- **操作**: WASD キーでプレイヤー（P）を移動
- **終了**: ESC キーまたはウィンドウの × ボタン
- **移動カウンター**: 各移動がシェルに表示される

## 🛠️ 技術仕様

- **言語**: C
- **グラフィックライブラリ**: MiniLibX (Linux 版)
- **コンパイル**: 42 Norm 準拠、`-Wall -Wextra -Werror`
- **メモリ管理**: リークなし、適切な解放処理
- **ファイル読み込み**: get_next_line 実装使用

## 📋 要件

### Linux 環境

```bash
# 必要なパッケージをインストール
sudo apt-get update
sudo apt-get install gcc make xorg libx11-dev libxext-dev libbsd-dev
```

### MiniLibX の取得

`minilibx-linux/` はリポジトリに含まれていない（`.gitignore` 対象）ため、ビルド前にリポジトリ直下へ配置する。

```bash
git clone https://github.com/42Paris/minilibx-linux.git minilibx-linux
```

## 🚀 コンパイル・実行

```bash
# コンパイル
make

# 実行
./so_long [マップファイル.ber]

# 例
./so_long map/map_correct.ber

# クリーンアップ
make clean    # オブジェクトファイル削除
make fclean   # 実行ファイルも削除
make re       # 再コンパイル
```

## 🗺️ マップ形式

### 有効な文字

- `1`: 壁
- `0`: 空きスペース
- `P`: プレイヤー開始位置（1 つのみ）
- `E`: 出口（1 つのみ）
- `C`: 収集アイテム（1 つ以上）

### マップ要件

- `.ber`拡張子
- 長方形形状
- 壁で完全に囲まれている
- 有効なパスが存在する

## 📁 プロジェクト構造

```
Solong/
├── src/                 # ソースファイル
│   ├── map.c           # マップ読み込み
│   ├── map_checker.c   # マップ形式の検証
│   ├── flood_fill.c    # 到達可能性判定
│   ├── render.c        # 描画処理
│   ├── render_mouv.c   # 移動処理
│   ├── texture.c       # main・キー処理
│   ├── cleanup.c       # リソース解放・終了処理
│   └── ...
├── includes/           # ヘッダファイル
├── libft/             # 42ライブラリ（get_next_line を含む）
├── minilibx-linux/    # MiniLibX Linux版（別途取得、git 管理外）
├── textures/          # ゲーム画像
├── map/              # テストマップ
├── tests/            # テストスクリプト
└── Makefile
```

## 🧪 テスト

```bash
make
./tests/run_tests.sh              # 不正マップがエラー終了するか、有効マップで起動するかを確認
VALGRIND=1 ./tests/run_tests.sh   # エラー系ケースを valgrind でリークチェック
```

- 不正なマップでは `Error` で始まるメッセージを標準エラーに出力し、終了コード 1 で終了する
- 有効マップの起動確認は `DISPLAY` があるか `xvfb-run` が使える環境でのみ実行される
- GitHub Actions（`.github/workflows/ci.yml`）で、ビルド・再リンクの有無・上記テスト・norminette を実行する

### テストマップ（`map/`）

| ファイル | 内容 |
| --- | --- |
| `map_correct.ber`, `map_minimal.ber` | 正常なマップ |
| `map_empty.ber` | 空ファイル |
| `map_empty_line.ber` | 途中に空行 |
| `map_not_rectangle.ber` | 長方形でない |
| `map_unknown_char.ber` | 未知の文字 |
| `map_not_closed.ber` | 壁で囲まれていない |
| `map_one_line.ber` | 1 行だけ |
| `map_no_player.ber` / `map_noexit.ber` / `map_no_collect.ber` | P / E / C がない |
| `map_multiplayer.ber` | プレイヤーが複数 |
| `map_unreachable.ber` | 収集アイテム・出口に到達できない |
| `map_exit_blocks.ber` | 出口を通らないと取れない収集アイテム（出口は収集完了まで通れない） |

## ✅ 実装機能

### 必須機能

- [x] マップ読み込み・検証
- [x] グラフィック表示
- [x] キー入力処理
- [x] 移動制限（壁判定）
- [x] 収集アイテム取得
- [x] ゲームクリア判定
- [x] 移動カウンター
- [x] 適切な終了処理

### セキュリティ

- [x] メモリリーク防止
- [x] セグメンテーションフォルト対策
- [x] 不正ファイルアクセス防止
- [x] バッファオーバーフロー対策

## 🏆 42 評価基準

- **Norm**: 42 コーディング規約準拠
- **エラーハンドリング**: 包括的なエラー処理
- **メモリ管理**: リークなし
- **機能性**: 全要件実装
- **効率性**: get_next_line 使用による高速化

## 📝 開発ノート

### 最適化実装

- **get_next_line**: 1024 バイトバッファによる高速ファイル読み込み
- **描画**: 現状は `mlx_loop_hook` で毎フレーム全体を再描画している（課題の「必要な要素のみ再描画」には未対応）
- **メモリ管理**: static 変数による適切な管理

### Linux 専用設定

- X11 ライブラリ使用
- Linux 環境のキーコード対応
- 条件付きコンパイル削除済み

---

**作成者**: 42 Student
**プロジェクト**: So_long
**環境**: Linux (Ubuntu/Debian 推奨)
