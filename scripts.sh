#!/bin/bash

case $1 in
 'dev')
   COMMAND="find src/ | entr meson test --verbose --timeout-multiplier 0.2 -C build ${@: 2}"
    ;;
  *)
    echo "Please specify a command"
    ;;
esac


if [ ${DRY_RUN=0} -eq 1 ]; then
  echo $COMMAND
else
  bash -c "$COMMAND"
fi
