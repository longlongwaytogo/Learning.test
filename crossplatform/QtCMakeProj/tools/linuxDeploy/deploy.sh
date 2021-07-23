# ~/.bashrc: executed by bash(1) for non-login shells.
 
echo deploy
export QTDIR=/opt/Qt5.12.10/5.12.10/gcc_64
export PATH=$QTDIR/bin:$QTDIR/plugins:$PATH
export LD_LIBRARY_PATH=$QTDIR/lib:$LD_LIBRARY_PATH

echo $1 $2 $3
$1 $2 $3


