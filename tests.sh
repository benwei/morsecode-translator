#!/bin/sh
BINFILE=./morse
pass_count=0
fail_count=0

inc_pass_count() {
    pass_count=$((pass_count + 1))
}

inc_fail_count() {
    fail_count=$((fail_count + 1))
}

## testeq(casedesc, errmsg, op1, op2)
testeq() {
    casedesc="$1"
    errmsg="$2"
    op1="$3"
    op2="$4"
    if [ "$op1" = "$op2" ]; then
         echo "[passed]: $casedesc"
         inc_pass_count
         return 0
    fi
    echo "[failed]: $casedesc $errmsg ($op1) is not equal ($op2)"
    inc_fail_count
    return 1
}

testsummary() {
    echo "summary: $((fail_count + pass_count)) , $pass_count passed and $fail_count failed tests"
    return $fail_count
}

## basic testing with cli input
r=`./$BINFILE "...."`
testeq "one morse code" "error" "$r" "H" 

r=`./$BINFILE '.- -... -.-. -.. . ..-. --. .... .. .--- -.- .-.. --'`
testeq "multiple morse codes" "error" "$r" "ABCDEFGHIJKLM" 

r=`./$BINFILE '-. --- .--. --.- .-. ... - ..- ...- .-- -..- -.-- --..'`
testeq "multiple morse codes2" "error" "$r" "NOPQRSTUVWXYZ" 

r=`./$BINFILE '.---- ..--- ...-- ....- ..... -.... --... ---.. ----. -----'`
testeq "numbers" "error" "$r" "1234567890" 

r=`./$BINFILE '.... ....- \. \- / \x20 \x651 --- -- - .. .'`
testeq "wrong escape char \xG" "error" "$r" "H4.-/ eOMTIE" 

./$BINFILE "... \xG .... -" > /dev/null
ret=$?
testeq "test wrong escape char \xG" "error" $ret 2 

testsummary
exit $?
