# WASIP1 Broken Build with CGo

## 小结
### cgo 并不支持编译为 wasm
相关 issue：[unknown ptrSize for $GOARCH "wasm"](https://github.com/golang/go/issues/40543)

### 编译过程报错的函数调用栈追踪

```
|-runBuild                                      // https://github.com/golang/go/blob/go1.22.4/src/cmd/go/internal/work/build.go#L462
  |-Builder.AutoAction                          // https://github.com/golang/go/blob/go1.22.4/src/cmd/go/internal/work/action.go#L430
  |-Builder.Do                                  // https://github.com/golang/go/blob/go1.22.4/src/cmd/go/internal/work/exec.go#L72
    |-buildActor.Act                            // https://github.com/golang/go/blob/go1.22.4/src/cmd/go/internal/work/action.go#L459
      |-Builder.build                           // https://github.com/golang/go/blob/go1.22.4/src/cmd/go/internal/work/exec.go#L450
        |-gofiles := str.StringList(p.GoFiles)  // https://github.com/golang/go/blob/go1.22.4/src/cmd/go/internal/work/exec.go#L591
          |-load.NoGoError                      // https://github.com/golang/go/blob/go1.22.4/src/cmd/go/internal/work/exec.go#L796
```

其中，`gofiles := str.StringList(p.GoFiles)` 这行是将 `Builder.build` 函数的形参 `a.Package.PackagePublic.GoFiles` 赋给局部变量 `gofiles`。

由 `PackagePublic` 结构体对 [GoFiles](https://github.com/golang/go/blob/go1.22.4/src/cmd/go/internal/load/pkg.go#L94) 字段的定义和注释
```go
...
GoFiles           []string `json:",omitempty"` // .go source files (excluding CgoFiles, TestGoFiles, XTestGoFiles)
CgoFiles          []string `json:",omitempty"` // .go source files that import "C"
...
```

可见，wit-bindgen 生成的 bindings 包没有任何满足 `GoFiles` 要求的文件，导致 `GoFiles` 的长度为 0，从而触发编译报错。

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
