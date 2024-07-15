#!/bin/bash

rm -rf out

mkdir -p out

GOOS=wasip1 GOARCH=wasm go build -v -o out/hello-world.wasm .
