
FILENAME=/tmp/checktarget-`date +%s`
echo "void test() {}" > ${FILENAME}.cc
gcc -o ${FILENAME}.o -c ${FILENAME}.cc
CHECKTARGET=`file ${FILENAME}.o | tr "\n" ' ' | awk '{split($0,a," "); print a[6] " " a[7]}'`
rm -rf ${FILENAME}.cc
rm -rf ${FILENAME}.o

if [ "${CHECKTARGET}" = "Intel 80386," ] ; then
	TARGETARCH="x86"
elif [ "${CHECKTARGET}" = "AMD x86-64," ] ; then
	TARGETARCH="x86_64"
elif [ "${CHECKTARGET}" = "x86-64, version" ] ; then
        TARGETARCH="x86_64"
else
	TARGETARCH="unknown"
	echo ${CHECKTARGET}
fi

echo $TARGETARCH

