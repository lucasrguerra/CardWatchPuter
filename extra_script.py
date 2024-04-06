Import("env")

env.Append(
    LINKFLAGS=[
        "-zmuldefs"
    ]
)
