#!/bin/bash

tmpdir="$(mktemp -d)"
ls /dev > "${tmpdir}/a"
echo -n "Plz insert||extract device and press any key:"
read
ls /dev > "${tmpdir}/b"
diff "${tmpdir}/a" "${tmpdir}/b" | grep -oP '(?<=[><] ).*'
