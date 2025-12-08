#!/bin/sh

function run() {
    local target=${1:-main}
    printf "executing target: %s\n" $target
    case "$target" in
        test)
            pytest tests.py --verbose
            ;;
        main)
            python main.py
            ;;
    esac

}

function setup_python() {
    local envpath="$PWD/env"
    if [[ ! -d "$envpath" ]]; then
        local python_v=$(python --version)
        printf "Setting up python venv for for %s\n" $python_v
        python -m venv $envpath
    fi

    printf "Activating Python VirtualEnv\n"
    source "$envpath/bin/activate"
}

setup_python
