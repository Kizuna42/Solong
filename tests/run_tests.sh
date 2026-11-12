#!/usr/bin/env bash
# so_long のマップ検証テスト。
#   使い方: make && ./tests/run_tests.sh
#   VALGRIND=1 を指定すると、エラー系のケースを valgrind でリークチェックする。
#   有効マップの起動確認は DISPLAY があるか xvfb-run が使える場合のみ実行する。
set -u
cd "$(dirname "$0")/.." || exit 1

BIN=./so_long
PASS=0
FAIL=0

if [ ! -x "$BIN" ]; then
	echo "$BIN が見つかりません。先に make を実行してください。" >&2
	exit 1
fi

run_bin() {
	if [ "${VALGRIND:-0}" = "1" ]; then
		valgrind -q --leak-check=full --errors-for-leak-kinds=definite \
			--error-exitcode=42 "$BIN" "$@"
	else
		"$BIN" "$@"
	fi
}

# エラーで終了し（終了コード != 0、valgrind のエラー 42 やタイムアウトではない）、
# stderr の 1 行目が "Error" であることを確認する
err_case() {
	local desc=$1
	shift
	local err status
	err=$(timeout 10 bash -c 'run_bin "$@"' _ "$@" 2>&1 >/dev/null)
	status=$?
	if [ "$status" -ne 0 ] && [ "$status" -ne 42 ] && [ "$status" -lt 124 ] \
		&& [ "$(printf '%s\n' "$err" | head -n 1)" = "Error" ]; then
		echo "ok   - $desc"
		PASS=$((PASS + 1))
	else
		echo "FAIL - $desc (exit=$status)"
		printf '%s\n' "$err" | sed 's/^/       /'
		FAIL=$((FAIL + 1))
	fi
}

export -f run_bin
export BIN

err_case "引数なし"
err_case "引数が多すぎる" map/map_correct.ber map/map_correct.ber
err_case "拡張子が .ber でない" map/map_correct.txt
err_case "存在しないファイル" map/does_not_exist.ber
err_case "空ファイル" map/map_empty.ber
err_case "途中に空行" map/map_empty_line.ber
err_case "長方形でない" map/map_not_rectangle.ber
err_case "未知の文字" map/map_unknown_char.ber
err_case "壁で囲まれていない" map/map_not_closed.ber
err_case "1 行だけのマップ" map/map_one_line.ber
err_case "プレイヤーなし" map/map_no_player.ber
err_case "出口なし" map/map_noexit.ber
err_case "収集アイテムなし" map/map_no_collect.ber
err_case "プレイヤーが複数" map/map_multiplayer.ber
err_case "到達不能" map/map_unreachable.ber
err_case "出口を通らないと取れない収集アイテム" map/map_exit_blocks.ber

# 有効なマップ: ウィンドウを開いてループに入るので、timeout で止まれば成功とみなす
expect_running() {
	local map=$1 runner=() status
	if [ -n "${DISPLAY:-}" ]; then
		runner=()
	elif command -v xvfb-run >/dev/null 2>&1; then
		runner=(xvfb-run -a)
	else
		echo "skip - 有効マップ $map（DISPLAY も xvfb-run もない）"
		return
	fi
	timeout 3 "${runner[@]}" "$BIN" "$map" >/dev/null 2>&1
	status=$?
	if [ "$status" -eq 124 ] || [ "$status" -eq 0 ]; then
		echo "ok   - 有効マップ $map が起動する"
		PASS=$((PASS + 1))
	else
		echo "FAIL - 有効マップ $map (exit=$status)"
		FAIL=$((FAIL + 1))
	fi
}

expect_running map/map_correct.ber
expect_running map/map_minimal.ber

echo "passed: $PASS, failed: $FAIL"
[ "$FAIL" -eq 0 ]
