package main

import (
	"fmt"
	"os"

	"./file"
)

func main() {
	hello := []byte("hello\n")
	file.Stdout.Write(hello)
	f, err := file.Open("/does/not/exist")
	if f == nil {
		fmt.Printf("can not open file; err=%s\n", err)
		os.Exit(1)
	}
}
