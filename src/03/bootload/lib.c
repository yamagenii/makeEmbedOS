#include "defines.h"
#include "serial.h"
#include "lib.h"

void *memset(void *b, int c, long len){
	//メモリを特定パターンで埋める
	char *p;
	for (p = b; len > 0; len--){
		*(p++) = c;
	}
	return b;
}

void *memcpy(void *dst, const void *src, long len){
	//メモリのコピーを行う
	char *d = dst;
	const char *s = src;
	for (;len > 0; len--){
		*(d++) = *(s++);
	}
	return dst;
}

int memcmp(const void *b1, const void *b2, long len){
	//メモリ上のデータを比較
	const char *p1 = b1 , *p2 = b2;
	for (; len > 0 ;len--){
		if (*p1 != *p2) return (*p1 > *p2) ? 1 : -1;
		p1++;
		p2++;
	}
	return 0;
}

int strlen(const char *s){
	//文字列の長さを返す
	int len;
	for(len = 0; *s; s++, len++){;}
	return len;
}

char *strcpy(char *dst, const char *src){
	//文字列のコピーを行う
	char *d = dst;
	for(;; dst++, src++){
		*dst = *src;
		if(!*src) break;
	}
	return d;
}

int strcmp(const char *s1, const char *s2){
	//文字列の比較を行う
	while(*s1 || *s2){
		if(*s1 != *s2) return (*s1 > *s2) ? 1: -1;
		s1++;
		s2++;
	}
	return 0;
}

int strncmp(const char *s1, const char *s2, int len){
	//長さ制限有りで文字列を比較する
	while((*s1 || *s2) && (len > 0)) {
		if (*s1 != *s2) return (*s1 > *s2) ? 1: -1;
		s1++;
		s2++;
		len--;
	}
	return 0;
}

int putc(unsigned char c){
	if (c == '\n'){
		serial_send_byte(SERIAL_DEFAULT_DEVICE, '\r');
	}
	return serial_send_byte(SERIAL_DEFAULT_DEVICE, c);
}

//printfは難しいから
int puts(unsigned char *str){
	while(*str){
		putc(*(str++));
	}
	return 0;
}

//数値の16進数表示
int putxval(unsigned long value, int column){
	char buf[9];
	char *p;
	p = buf + sizeof(buf) - 1;
	*(p--) = '\0';
	if (!value && !column) column++;
	while (value || column){
		*(p--) = "0123456789abcdef"[value & 0xf];  //16新数表示にしてバッファに格納する
		value >>=4;                                //次の桁にすすめる
		if (column) column--;
	}
	puts(p+1);
	return 0;
}
