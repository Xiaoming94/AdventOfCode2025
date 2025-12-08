#!/bin/sh

function run() {
    local target=${1:-main}
    printf "executing target: %s\n" $target
    case "$target" in
        test)
            python -m unittest tests.py --verbose
            ;;
        main)
            python main.py
            ;;
    esac

}

function setup_python() {
    local envpath="$PWD/env"
    if [[ ! -d "$envpath" ]]; then
        printf "Setting up python venv for for %s\n" $(python --version)
        python -m venv $envpath
    fi
    source "$envpath/bin/activate"
}

setup_python
