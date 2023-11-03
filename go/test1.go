package test1

// import "fmt"

/* 
var int_g int = 10 // package
var Int_g int = 10 // export
*/

type test1 struct {
	str string
}
func NewTest1(str string) *test1 {
	return &test1{str}
}
func (t *test1) GetStr() string {
	return t.str
}
func (t *test1) SetStr(str string) {
	t.str = str
}
