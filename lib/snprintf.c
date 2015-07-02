snprintf(buff,sizeof(buff), "tcp://%s:%d", src, port);    
 //把长度为sizeof(buff) ，格式为tcp://%s:%d

	1- 如果格式化后的字符串长度 < size，则将此字符串全部复制到str中，
并给其后添加一个字符串结束符('\0')；

	2- 如果格式化后的字符串长度 >= size，则只将其中的(size-1)个字符复制到str中，
并给其后添加一个字符串结束符('\0')，返回值为欲写入的字符串长度。

