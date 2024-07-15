package main

import (
	"fmt"
	"reflect"

	"github.com/sammyne/wasip1-cgo-broken-build/bindings"
)

func init() {
	w := ExampleWorld{}
	bindings.SetBindings(w)
}

func main() {}

type ExampleWorld struct{}

func (w ExampleWorld) HelloWorld() string {
	t := reflect.TypeFor[ExampleWorld]()

	out := fmt.Sprintf("%s-%s", t.Name(), t.PkgPath())

	return "hello world :)" + out
}
