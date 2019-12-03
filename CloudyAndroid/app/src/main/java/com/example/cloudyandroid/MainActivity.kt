package com.example.cloudyandroid

import android.annotation.SuppressLint
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.widget.EditText
import android.widget.Toast
import kotlinx.android.synthetic.main.activity_main.*
import java.io.InputStream
import java.io.OutputStream
import java.lang.Exception
import java.net.InetAddress
import java.net.Socket
import kotlinx.coroutines.*
import kotlin.coroutines.CoroutineContext


class MainActivity : AppCompatActivity(),CoroutineScope {

    @SuppressLint("ResourceType")

    //코루틴 인터페이스 상속 및 추가
    private lateinit var mJob: Job

    override val coroutineContext: CoroutineContext
        get() = mJob + Dispatchers.Main


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        mJob = Job()

        //launch 정의





        var Msg = findViewById(R.id.etMsg) as EditText
        var etIP = findViewById<EditText>(R.id.etIp)


        //호스트 주소 선언 및 임시 주소 할당 (string)
        // 포트
        val PORT = 8080
        var socketCrt : Job

        //버튼 클릭 리스너
        btnSend.setOnClickListener {

            //hostIP = Integer.parseInt(etIP.text.toString())

            //addr에 에딧 텍스트 값 받기
            var addr  = etIP.text.toString()
            var sendMsg = Integer.parseInt(Msg.text.toString())

            //inetAddress 형으로 받기
            var hostIP = InetAddress.getByName(addr)

            var i : Int = 0
            socketCrt = launch(newSingleThreadContext("testThread")) {
                try {
                    Log.d("디버그", "socket init IP : " + hostIP + "PORT : " + PORT)
                    val sock = Socket(hostIP, PORT)
                    Log.d("디버그", "socket connected")
                    val outStream: OutputStream = sock.getOutputStream()
                    val inStream: InputStream = sock.getInputStream()



                    outStream.write(sendMsg)

                    sock.close()
                } catch (e: Exception) {
                    e.printStackTrace()
                    Log.e("디버그", e.toString())

                }
            }

        }


    }

    override fun onDestroy() {
        super.onDestroy()

        mJob.cancel()
    }
}
