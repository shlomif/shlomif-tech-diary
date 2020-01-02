assert(cond,err)=if(!cond,error(err))
myfunc()=4
assert(myfunc()==5,"myfunc should return 5")
