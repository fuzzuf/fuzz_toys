# repeat_message

# これは何

* 小さいビットマップ（非ゼロの箇所が少ない）生成をウリにしたターゲット
* オフセット0バイト目～7バイト目で指定された回数だけ、8バイト目以降の文字を表示してくれる

# 動かし方

```
$ echo -ne "\x03\x00\x00\x00\x00\x00\x00\x00Hello world!" | ./src/repeat_message/fuzz_toys-repeat_message
Hello world!
Hello world!
Hello world!
```