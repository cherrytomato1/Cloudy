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

class socketClass {

    lateinit var sock: Socket
    lateinit var outStream: OutputStream

    //코틀린 함수의 매개변수는 val 형식이므로 형식을 쓸 필요가 없다.

    fun socketConnect(IP: InetAddress, PORT: Int): Boolean {
        try {
            Log.d("디버그", "socket init IP : " + IP + "PORT : " + PORT)
            sock = Socket(IP, PORT)
            Log.d("디버그", "socket connected")
            outStream = sock.getOutputStream()

            outStream.write("test".toByteArray())
            //val inStream: InputStream = sock.getInputStream()

            //sock.close()
            //Log.d("디버그", "socket closed")
            return TRUE

        } catch (e: Exception) {
            e.printStackTrace()
            Log.e("디버그", e.toString())

            return FALSE

        }
    }

    fun socketSend(msg: String) {
        GlobalScope.launch {
            Log.d("디버그", "outStream")
            outStream.write(msg.toByteArray())
        }
    }

    fun sockend() {
        GlobalScope.launch {
            Log.d("디버그", "socketClose")
            sock.close()
        }
    }

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