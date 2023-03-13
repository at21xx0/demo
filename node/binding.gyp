{
	"targets": [
		{
			"target_name": "test",
			"defines": ["ENABLE_SLEEP=1"],
			"include": ["."],
			"cflags!": ["-Wall"],
			"conditions": [
				['OS=="linux"', {}],
				['OS=="mac"', {}],
				['OS=="win"', {
					"defines": ["WIN32"]
				}]
			],
			"sources": ["test.c"]
		}
	]
}


