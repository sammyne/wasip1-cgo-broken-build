# WASIP1 Broken Build with CGo

## Environment
- Go 1.22.4

Output of `go env` command goes as

```bash
GO111MODULE=''
GOARCH='amd64'
GOBIN=''
GOCACHE='/root/.cache/go-build'
GOENV='/root/.config/go/env'
GOEXE=''
GOEXPERIMENT=''
GOFLAGS=''
GOHOSTARCH='amd64'
GOHOSTOS='linux'
GOINSECURE=''
GOMODCACHE='/go/pkg/mod'
GONOPROXY=''
GONOSUMDB=''
GOOS='linux'
GOPATH='/go'
GOPRIVATE=''
GOPROXY='https://goproxy.woa.com,direct'
GOROOT='/usr/local/go'
GOSUMDB='sum.woa.com+643d7a06+Ac5f5VOC4N8NUXdmhbm8pZSXIWfhek5JSmWdWrq7pLX4'
GOTMPDIR=''
GOTOOLCHAIN='local'
GOTOOLDIR='/usr/local/go/pkg/tool/linux_amd64'
GOVCS=''
GOVERSION='go1.22.4'
GCCGO='gccgo'
GOAMD64='v1'
AR='ar'
CC='gcc'
CXX='g++'
CGO_ENABLED='1'
GOMOD='/github.com/sammyne/wasip1-cgo-broken-build/go.mod'
GOWORK=''
CGO_CFLAGS='-O2 -g'
CGO_CPPFLAGS=''
CGO_CXXFLAGS='-O2 -g'
CGO_FFLAGS='-O2 -g'
CGO_LDFLAGS='-O2 -g'
PKG_CONFIG='pkg-config'
GOGCCFLAGS='-fPIC -m64 -pthread -Wl,--no-gc-sections -fmessage-length=0 -ffile-prefix-map=/tmp/go-build1744286471=/tmp/go-build -gno-record-gcc-switches'
```

## Project Layout

```
|-main.go         // depends on C-based bindings APIs
|-bindings
  |-bindings.c    // implementation of C-based bindings
  |-bindings.go   // adapters of C-based bindings APIs
  |-bindings.h    // headers of C-based bindings
```

## Problem Reproduction

Building the project as

```bash
GOOS=wasip1 GOARCH=wasm go build -v -o hello-world.wasm .
```

produces errors as
```bash
package github.com/sammyne/wasip1-cgo-broken-build
        imports github.com/sammyne/wasip1-cgo-broken-build/bindings: build constraints exclude all Go files in /github.com/sammyne/wasip1-cgo-broken-build/bindings
```

Really appreciate if someone could help me out~

## References
- https://go.dev/wiki/WebAssembly#go-webassembly-talks
