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
        launch {
            //UI 스레드 에서 동작 합니다
            print(Thread.currentThread().name)
            //dispatcher 를 사용하여 context 사이를 전환 합니다
            val deferred = async(Dispatchers.Default) {
                //백그라운드 스레드 에서 동작합니다
                10 + 10
            }
            //UI 스레드 에서 동작 합니다
            print(deferred.await())
        }



        var Msg = findViewById(R.id.etMsg) as EditText
        var etIP = findViewById<EditText>(R.id.etIp)
        var sendMsg = "t".toByteArray()

        //호스트 주소 선언 및 임시 주소 할당 (string)
        var addr ="172.20.10.11"
        // 포트
        val PORT = 8080

        //버튼 클릭 리스너
        btnSend.setOnClickListener {

            //hostIP = Integer.parseInt(etIP.text.toString())

            //addr에 에딧 텍스트 값 받기
            addr  = etIP.text.toString()

            //inetAddress 형으로 받기
            var hostIP = InetAddress.getByName(addr)


            val socketCrt : Job = launch(){}
            try{
                Log.d("디버그", "socket init IP : "+hostIP + "PORT : " + PORT)
                val sock  = Socket(hostIP,PORT)
                Log.d("디버그", "socket connected")
                val outStream : OutputStream = sock.getOutputStream()
                val inStream : InputStream = sock.getInputStream()

                Toast.makeText(this,addr,Toast.LENGTH_LONG).show()

                outStream.write(sendMsg)

                sock.close()
            }
            catch (e:Exception){
                Log.e("디버그", "socket error")
                e.printStackTrace()
            }


        }
    }

    override fun onDestroy() {
        super.onDestroy()

        mJob.cancel()
    }
}
