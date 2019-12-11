package com.example.cloudyandroid

import android.util.Log
import android.widget.Toast
import kotlinx.android.synthetic.main.activity_control.*
import java.io.OutputStream
import java.lang.Boolean.FALSE
import java.lang.Boolean.TRUE
import java.lang.Exception
import java.net.Inet4Address
import java.net.InetAddress
import java.net.Socket

public class socketClass{

    //코틀린 함수의 매개변수는 val 형식이므로 형식을 쓸 필요가 없다.
    public fun socketConnect(IP : InetAddress, PORT : Int) : Boolean{
        try {
            Log.d("디버그", "socket init IP : " + IP + "PORT : " + PORT)
            val sock = Socket(IP, PORT)
            Log.d("디버그", "socket connected")

            val outStream: OutputStream = sock.getOutputStream()
            //val inStream: InputStream = sock.getInputStream()
            sock.close()
            return TRUE

        } catch (e: Exception) {
            e.printStackTrace()
            Log.e("디버그", e.toString())

            return FALSE

        }
    }
}