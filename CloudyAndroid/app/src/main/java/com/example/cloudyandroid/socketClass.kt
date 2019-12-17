package com.example.cloudyandroid

import android.util.Log
import android.widget.Toast
import kotlinx.android.synthetic.main.activity_control.*
import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.launch
import kotlinx.coroutines.runBlocking
import java.io.OutputStream
import java.lang.Boolean.FALSE
import java.lang.Boolean.TRUE
import java.lang.Exception
import java.net.Inet4Address
import java.net.InetAddress
import java.net.Socket

//소켓함수의 행동을 갖고 있는 소켓 클래스
class socketClass {

    //소켓 인스턴스 생성, 아웃스트림 인스턴스 생성(클래스 내의 모든 함수가 공유하도록)
    lateinit var sock: Socket
    lateinit var outStream: OutputStream

    //코틀린 함수의 매개변수는 val 형식이므로 형식을 쓸 필요가 없다.
    //소켓 연결 함수(IP,PORT)
    fun socketConnect(IP: InetAddress, PORT: Int): Boolean {
        try {
            //소켓 연결 시작 알림 로그
            Log.d("디버그", "socket init IP : " + IP + "PORT : " + PORT)
            runBlocking { sock = Socket(IP, PORT)}
            //연결 성공시 아웃풋 스트림 설정
            Log.d("디버그", "socket connected")
            outStream = sock.getOutputStream()
            //test를 보내어 연결 성공 확인
            outStream.write("test".toByteArray())
            //val inStream: InputStream = sock.getInputStream()

            //sock.close()
            //Log.d("디버그", "socket closed")
            //성공 여부 반환
            return TRUE

        } catch (e: Exception) {
            //실패 시 로그 출력
            e.printStackTrace()
            Log.e("디버그", e.toString())

            return FALSE

        }
    }

    //소켓 전송 함수 : 새로운 쓰레드를 생성하여 보냄(소켓통신)
    fun socketSend(msg: String) {
        GlobalScope.launch {
            Log.d("디버그", "outStream")
            outStream.write(msg.toByteArray())
        }
    }
    //소켓 전송 함수 : 새로운 쓰레드를 소켓을 종료함
    fun sockend() {
        GlobalScope.launch {
            Log.d("디버그", "socketClose")
            sock.close()
        }
    }
    //소켓이 열려있는지 닫혀있는지 확인
    fun sockCHECK():Boolean{
        return runBlocking {
            Log.d("디버그","socket check")
            when(sock.isClosed) {
                true ->false
                else -> true
            }
        }
    }
}