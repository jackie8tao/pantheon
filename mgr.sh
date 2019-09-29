# -*- coding: utf-8 -*-
# !/usr/bin/env bash

if ! [[ -x /usr/bin/python3 ]]; then 
    echo "python3 dont exist"
    exit -1
fi

case $1 in
    create)
        if [[ -z "$2" ]]; then
            echo "project name is empty"
            exit -1
        fi
        python3 _scripts/project.py $2
        ;;
    *)
        echo "./mgr.sh {create}"
        ;;
esac

exit 0