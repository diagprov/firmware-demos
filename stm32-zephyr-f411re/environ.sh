#!/bin/sh

([[ -n $ZSH_EVAL_CONTEXT && $ZSH_EVAL_CONTEXT =~ :file$ ]] || 
 [[ -n $KSH_VERSION && $(cd "$(dirname -- "$0")" &&
    printf '%s' "${PWD%/}/")$(basename -- "$0") != "${.sh.file}" ]] || 
 [[ -n $BASH_VERSION ]] && (return 0 2>/dev/null)) && SCRIPT_SOURCED=1 || SCRIPT_SOURCED=0


if [[ $SCRIPT_SOURCED -eq "0" ]]; then
    echo "Please source this script."
fi

export ZEPHYR_TOOLCHAIN_VARIANT=cross-compile
export CROSS_COMPILE=/opt/arm/arm-eabi-latest/bin/arm-none-eabi-
