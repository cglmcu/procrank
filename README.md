# procrank
C files and header files are copied from android 7.1, the procrank can both use on linux and android devices,or others

# HOWTO
first in your device kernel, you should slect CONFIG_PROC_PAGE_MONITOR=y 
then
```
# download code  
# export CC=your crosscompile
# cd procrank  
# make  
# sudo make install  
# ./procrank
