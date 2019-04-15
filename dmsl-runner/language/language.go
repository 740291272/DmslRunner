package language

import (
	"github.com/740291272/DmslRunner/dmsl-runner/language/dmsl"
)
	
type runFn func([]string, string) (string, string, error)

var languages = map[string]runFn{
	"dmsl":         dmsl.Run,
}

func IsSupported(lang string) bool {
	_, supported := languages[lang]
	return supported
}

func Run(lang string, files []string, stdin string) (string, string, error) {
	return languages[lang](files, stdin)
}
