package com.example.cloudyandroid;

import android.annotation.SuppressLint
import android.content.Intent
import android.os.Bundle
import android.support.v7.app.AppCompatActivity
import android.util.Log
import android.widget.EditText
import android.widget.Toast
import kotlinx.android.synthetic.main.activity_main.*
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.Job
import kotlinx.coroutines.launch
import java.io.OutputStream
import java.lang.Exception
import java.net.InetAddress
import java.net.Socket
import kotlin.coroutines.CoroutineContext

class controlActivity : AppCompatActivity(), CoroutineScope {

    @SuppressLint("ResourceType")

    //코루틴 인터페이스 상속 및 추가
    private lateinit var mJob: Job

    override val coroutineContext: CoroutineContext
        get() = mJob + Dispatchers.Main


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_control)
        mJob = Job()

        var socketCrt: Job


        socketCrt = launch(Dispatchers.Default) {
            try {
                Log.d("디버그", "socket init IP : " + hostIP + "PORT : " + PORT)
                val sock = Socket(hostIP, PORT)
                Log.d("디버그", "socket connected")
                Toast.makeText(applicationContext, "소켓 연결됨", Toast.LENGTH_LONG).show()
                val outStream: OutputStream = sock.getOutputStream()
                //val inStream: InputStream = sock.getInputStream()

                outStream.write(sendMsg)

                sock.close()

            } catch (e: Exception) {
                e.printStackTrace()
                Log.e("디버그", e.toString())

            }
        }
    }

    override fun onDestroy() {
        super.onDestroy()

        mJob.cancel()
    }
}
