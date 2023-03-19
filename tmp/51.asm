mark1:
	mov P0, #0
	; 12 12D 十进制
	; 00001100B 二进制
	; 0CH 十六进制; 字母开始要在前面加0

	; 单字节指令
	NOP ; 空操作，常用于4字节对其
	INC DPTR ; DPTR = DPTR + 1
	; 寄存器 R0 , R1 ..., R7 ; Rn
	mov A, R7 ; 11101rrr; rrrB = 7

	; 双字节指令
	mov A, #47H
	; 三字节指令
	mov 80H, #65H
	
	; 常见符号
	; Rn ; 寄存器R0-R7 ; 储存立即数
	; Ri ; R0 R1 ;储存间接地址
	; ACC A ; 累加器
	; @ ; 间接寻址方式寄存器符号
	; #data ; 八位立即数
	; #data16 ; 十六位立即数 #327FH
	; direct ; 80H ; RAM 或 SFR 地址
	; addr11 ; 11位目的地址 ； 用于 AJMP ACALL 指令 ; 目的地址必须与下一条指令的第一个字节在同一个 ２ＫＢ程序存储器地址空间之内
	; addr16 ; 16位目的地址 ;
	; rel ; 八位带符号补码 ; -128 ~ 127 数字
	; bit ; RAM 或 SFR 中可寻址位
	; C CY ; A 中 进位标志
	; / ; 加在位地址前 表示取反
	; (x) ; 寄存器或地址中的内容
	; ((x)) ; 嵌套
	; A ; 累加器
	; B ; 寄存器，用于 mul div
	; C ; 进位标志或进位位
	; SP ; 堆栈指针
	; PC ; 程序执行位置
	
	; 执行 从 0000h开始
	
	; 寻址方式
	mov A, #7FH ; 立即寻址 ; (A) = 7FB
	mov A, 80H ; 间接寻址 ; (A) = (80H) ; direct
	mov A, P0 ; 间接寻址 ; (A) = (P0) ; direct
	mov A, R7 ; 寄存器寻址
	mul AB ; 寄存器寻址
	inc R0 ; 寄存器寻址
	mov B, R7 ; 间接寻址
	; 寄存器寻址指令占一字节 间接寻址更长
	mov A, @R0 ; 寄存器间接寻址 ; (A) = ((R0)) @ 后可以是 DPTR, R0, R1
	movc A, @A+DPRT ; 寄存器加变地址寄存器间接寻址 ; 适用于 DPTR 或 PC
	jmp @A+DPTR ; 同上
	movc A, @A+PC ; 同上
	jc 80H ; 相对寻址，相对于PC ; -128 ~ 127 ; jc 大小不可忽略
	; 位寻址 例如
	; clr C
	; mov C, 30H
	; setb psw.4 ; (PSW.4) = 1

	; 指令系统
	;	 包括 数据传输 算数运算 逻辑运算 位操作 控制转移
	;  
	; mov A, Rn ; Rn 可换为 direct @Ri #data
	; mov Rn, A ; A 可替换为 direct #data
	; mov direct, A; A 可替换为 Rn direct2 @Ri #data
	; ov @Ri, A ; A 可替换为 direct #data
	; mov DPTR, #data
	; movc A, @A+DPTR ; 读 A+DPTR 到 A
	; movc A, @A+PC ; 
	; movx A, @Ri ; 读取外部 RAM 单元 ; @Ri 可替换为 @DPTR 
	; movx Ri, A ; A 内容送至外部 RAM ;
	; 
	; push direct ; 入栈 ; (SP) = (SP) + 1 (SP) = (direct)
	; pop direct ; 出栈 ; (direct) = (SP) (SP) = (SP) - 1
	; xch A, Rn ; A 与 Rn 交换; Rn 可替换为 direct @Ri
	; xchd A, @Ri ; A 低四位与 @Ri 低四位交换
	; swap A ; A 高四位与低四位交换

	; 算数运算指令
	; add A, Rn ; (A) = (A) + (Rn) ; Rn 可替换为 direct @Ri #data
	; addc A, Rn ; (A) = (A) + (Rn) + (CY) ; (CY) 为上次运算进位标志 ; Rn 可替换为 direct @Ri #data 
	; inc A ; (A) = (A) + 1 ; A 可替换为 Rn direct @Ri DPTR 
	; dec A ; (A) = (A) - 1 ; A 可替换为 Rn direct @Ri
	; da A ; 对A进行十进制调整
	; subb A, Rn ; (A) = (A) - (Rn) - (CY) ; (CY) 为上次运算进位标志 ; Rn 可替换为 direct @Ri #data 
	; mul AB ; (AB) = (A) * (B) ;
	; div AB ; (AB) = (A) / (B) ;
	; inc DPTR ; 不影响进位标志
	; da A ; 如计算 #36h + 45h  add 计算后结果为 #7B DA A 后是 #81h ;
	; dec ; 不影响 标志
	; div AB ; 若 (B) = 0 (OV) = 1 ;

	; 逻辑运算指令
	; clr A ; (A) = 0
	; cpl A ; (A) = ~(A)
	; rl A ; (A) = ((A) >> 7) | ((A) << 1) 
	; rlc A ; (F0) = ((A) & 80H) >> 7  ((A) = (A) << 1) | C  (C) = (F0)
	; rr A ; (A) = (A) >> 1
	; rrc A ; (F0) = *A) & 1H  (A) = ((A) >> 1) | (C << 7)  (C) = (F0) 
	; anl A, Rn ; (A) = (A) & (Rn) ; Rn 可替换为 direct @Ri #data
	; aNl direct, A ; (direct) = (direct) & (A) ; (A) 可替换为 #data
	; orl A, Rn ; (A) = (A) | (Rn) ; Rn 可替换为 direct @Ri #data
	; orl direct, A ; (direct) = (direct) | (A) ; (A) 可替换为 #data
	; xrl A, Rn ; (A) = (A) ^ (Rn) ; Rn 可替换为 direct @Ri #data
	; xrl direct, A ; (direct) = (direct) ^ (A) ; (A) 可替换为 #data

	; 控制转移指令
	; ajmp addr11 ; 2 KB 内转移绝对转移，addr11 与AJMP 的下一指令必须在相同的2KB内(AJMP addr11 占2) ; (PC) = addr11
	; ljmp addr16 ; 64 KB 内转移 ; (PC) = addr16
	; sjmp rel ; 相对短转移 ; (PC) = (PC) + 2  (PC) = (PC) + rel ; SJMP rel 长为 2
	; jmp @A+DPTR ; 相对长转移 ; (PC) = (A) + (DPTR)
	; jz rel ; (A) == 0 转移 ; (PC) = (PC) + 2 + rel
	; jnz rel ; (A) != 0 转移 ; (PC) = (PC) + 2 + rel
	; cjne A, direct, rel ; (A) != (direct) 转移 ; (PC) = (PC) + 3 + rel ; direct 可替换为 #data
	; cjne Rn, #data, rel ; (Rn) != (#data) 转移 ; (PC) = (PC) + 3 + rel  (CY) = (Rn < #data )?1:0 ; Rn 可替换为 @Ri
	; djnz Rn, rel; (Rn) = (Rn) - 1  (Rn) != 0 转移 ; (PC) = (PC) + 3 + rel ; Rn 可替换为 direct
	; acall addr11 ; 2 KB 内绝对调用 ; (PC) = (PC) + 2  (SP) = (SP) + 1  ((SP)) = (PC) & FFH  (SP) = (SP) + 1  ((SP)) = (PC) >> 8  (PC) = addr11 ;
	; lcall addr16 ; 64 KB 内绝对调用 ; (PC) = (PC) + 3  (SP) = (SP) + 1  ((SP)) = (PC) & FFH  (SP) = (SP) + 1  ((SP)) = (PC) >> 8  (PC) = addr16 ;
	; ret ; 子程序返回 与调用连用 ; (PC) = ((PC) & FFH) | (((SP)) << 8)  (SP) = (SP) - 1 (PC) = ((PC) & FF00H) | ((SP))  (SP) = (SP) - 1 
	; reti ; 中断返回 ; 与 RET 相似 还要清除中断标志
	;

	; 位操作指令
	; mov C, bit ; (CY) = (bit)
	; mov bit, C ; (bit) = (C)
	; clr C ; (CY) = 0
	; clr bit ; (bit) = 0
	; cpl C ; (CY) = ~(CY)
	; cpl bit ; (bit) = ~(bit) 
	; setb C : (C) = 1
	; setb bit : (bit) = 1
	; anl C, bit ; (CY) = (C) & (bit)
	; anl C, /bit ; (CY) = (C) & (~(bit))
	; orl C, bit ; (CY) = (C) | (bit)
	; orl C, /bit ; (CY) = (C) | (~(bit))
	; jc rel ; (CY) = 1 ; (PC) = (PC) + 2 + rel
	; jnc rel ; (CY) = 0 ; (PC) = (PC) + 2 + rel
	; jb bit, rel ; (bit) = 1 ; (PC) = (PC) + 2 + rel
	; jnb bit, rel ; (bit) = 0 ; (PC) = (PC) + 2 + rel
	; jbc bit, rel ; (bit) = 1 ; (PC) = (PC) + 2 + rel  (bit) = 0
	; 
	; bit 表示方式
	; NEWEX0 BIT EX0
	; 0A8H IE.0 EX0 NEWEX0 ACC.0

	; 伪指令
	; org addr16 ; 设置地址
	; end ;
	; db 58h, 68h, 0, 23, 0, '0' ; 定义字节，数字可以不加# 把当前ROM地址填充位DB 后数据
	; dw 5868h, 23, '0', '00 ; 一次可以填充两字节
	; ds 20H ; 填充20个00h (NOP)
	; SUM EQU 80H ; SUM 被赋值 80H
	; AA EQU BB ; AA 赋值为 BB



	

