# -*- coding: utf-8 -*-
# !/usr/bin/env python3

# 项目结构定义
PROJARCH = {
    "README.md": {"type": "file"},
    ".gitignore": {"type": "file", "content": "/.vscode\n/.idea\n"},
    "codes": {
        "type": "dir",
        "children": {
            ".gitkeep": {
                "type": "file"
            }
        }
    },
    "images": {"type": "dir", "children": {".gitkeep": {"type": "file"}}},
    "doc": {
        "type": "dir",
        "children": {
            ".gitkeep": {
                "type": "file"
            }
        }
    }
}
