#!/bin/zsh

SELF_DIR="${${(%):-%x}:A:h}"
# https://stackoverflow.com/questions/9901210/bash-source0-equivalent-in-zsh
#     In the comment of the above page, `${(%):-%x}` is suggested,
#     which is the name of the current file.
# See also:
#     man zshexpn
#         Parameter Expansion
#         Modifiers
#     man zshmisc
#         Simple Prompt Escapes
# TODO: What does "P" modifier diffent from "A" modifier?
