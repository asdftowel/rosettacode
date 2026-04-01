#!/usr/bin/sh
prog="$prefix$name"
errs=0
grn=$(printf "\033[92m")
red=$(printf "\033[91m")
clr=$(printf "\033[0m")
if [ ! -x "$prog" ]
then
  echo 'Cannot find the compiled program in current directory.'
  exit 1
fi

check_print() {
    printf "Calling with %s... " "$1"
    case "$($prog $2)" in
      *"$3"*) printf "%sPASS%s\n" "$grn" "$clr" ;;
      *)      printf "%sFAIL%s\n" "$red" "$clr" 
              errs=$(($errs+1)) ;;
    esac
}

check_print 'an empty value' '' 'even or odd'
check_print 'a non-numeric argument' '-' 'a number'
check_print 'a number with an invalid sign' '^23' 'a number'
check_print 'an invalid number' '5&7' 'a number'
check_print 'a huge number' '9223372036854775808' 'outside'
check_print 'negative zero' '-0' 'is even'
check_print 'positive zero' '0' 'is even'
check_print 'a negative odd number' '-957' 'is odd'
check_print 'a negative even number' '-2000' 'is even'
check_print 'a positive odd number' '3' 'is odd'
check_print 'a positive even number' '400582' 'is even'

if [ "$errs" -eq 1 ]
then
  noun='test'
else
  noun='tests'
fi

if [ "$errs" -eq 0 ]
then
  echo 'All tests passed.'
  exit 0
else
  echo "$errs $noun failed."
  exit 1
fi