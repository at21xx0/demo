package main

import "testing"

// go test main.go main_test.go

func TestMax_1(t *testing.T) {
	m := max_1(1, 2)
	if m != 2 {
		t.Error("failed")
	}
}
