#!/bin/bash -ex
#
# Script for CI to test clang-format result
#
git --no-pager diff --ignore-submodules --name-only HEAD > /tmp/clang-format-diff

if [ -s "/tmp/clang-format-diff" ]; then
    echo "clang-format warning found"
    git diff --color=always
    exit 1 > /dev/null 2>&1
fi
