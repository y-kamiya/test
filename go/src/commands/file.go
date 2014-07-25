package file

import "syscall"

type File struct {
	fd   int
	name string
}

func newFile(fd int, name string) *File {
	if fd < 0 {
		return nil
	}
	return &File{fd, name}
}

var (
	Stdin  = newFile(syscall.Stdin, "/dev/stdin")
	Stdout = newFile(syscall.Stdout, "/dev/stdout")
	Stderr = newFile(syscall.Stderr, "/dev/stderr")
)

func OpenFile(name string, mode int, perm uint32) (file *File, err error) {
	r, e := syscall.Open(name, mode, perm)
	return newFile(r, name), e
}

const (
	O_RDONLY = syscall.O_RDONLY
	O_RDWR   = syscall.O_RDWR
	O_CREATE = syscall.O_CREAT
	O_TRUNC  = syscall.O_TRUNC
)

func Open(name string) (file *File, err error) {
	return OpenFile(name, O_RDONLY, 0)
}

func Create(name string) (file *File, err error) {
	return OpenFile(name, O_RDWR|O_CREATE|O_TRUNC, 0666)
}

func (file *File) Close() error {
	if file == nil {
		return syscall.EINVAL
	}
	e := syscall.Close(file.fd)
	file.fd = -1
	if e != nil {
		return e
	}
	return nil
}

func (file *File) Read(b []byte) (ret int, err error) {
	if file == nil {
		return -1, syscall.EINVAL
	}
	r, e := syscall.Read(file.fd, b)
	return int(r), e
}

func (file *File) Write(b []byte) (ret int, err error) {
	if file == nil {
		return -1, syscall.EINVAL
	}
	r, e := syscall.Write(file.fd, b)
	return int(r), e
}

func (file *File) String() string {
	return file.name
}
