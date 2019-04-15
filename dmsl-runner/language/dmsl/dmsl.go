package dmsl

import (
	"github.com/740291272/DmslRunner/dmsl-runner/cmd"
	"path/filepath"
)

func Run(files []string, stdin string) (string, string, error) {
	workDir := filepath.Dir(files[0])
	return cmd.RunStdin(workDir, stdin, "dmslrunner", files[0])
}
