package com.example.cloudyandroid;

import android.annotation.SuppressLint
import android.app.Activity
import android.content.Intent
import android.os.Bundle
import android.support.v7.app.AppCompatActivity
import android.util.Log
import android.view.MotionEvent
import android.view.View
import android.widget.EditText
import android.widget.Toast
import kotlinx.android.synthetic.main.activity_control.*
import kotlinx.android.synthetic.main.activity_main.*
import kotlinx.coroutines.*
import java.io.OutputStream
import java.lang.Boolean.TRUE
import java.lang.Exception
import java.net.InetAddress
import java.net.Socket
import kotlin.coroutines.CoroutineContext

class controlActivity : AppCompatActivity(), CoroutineScope {

    @SuppressLint("ResourceType")

    //코루틴 인터페이스 상속 및 추가
    private lateinit var mJob: Job
    lateinit var socket : Job
    //lateinit = 선언 이후 초기화
    lateinit var sock: socketClass


    override val coroutineContext: CoroutineContext
        get() = mJob + Dispatchers.Main


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_control)

        mJob = Job()
        Log.d("디버그", "control start")
        val bundle: Bundle? = intent.extras
        //? ->> nullable

        val hostIP = InetAddress.getByName(bundle!!.getString("IP"))
        val PORT = bundle!!.getInt("PORT")


        socket = Job()

        var checkBTN = 0
        sock = socketClass()


        //socket = launch(Dispatchers.Default) {
        socket = GlobalScope.launch {
            if (sock.socketConnect(hostIP, PORT) == TRUE) {
                //Toast.makeText(applicationContext,"connection success",Toast.LENGTH_SHORT).show()
                //스레드가 다른 액티비티에 토스트를 띄울 때 에러 발생
                btnFWD.setOnTouchListener { _: View, event ->
                    when (event.action) {
                        MotionEvent.ACTION_DOWN -> {
                            checkBTN = 1
                            true
                        }
                        else -> {
                            checkBTN = 0
                            true
                        }
                    }

                }
                btnLEFT.setOnTouchListener { _: View, event ->
                    when (event.action) {
                        MotionEvent.ACTION_DOWN -> {
                            checkBTN = 2
                            true
                        }
                        else -> {
                            checkBTN = 0
                            true
                        }
                    }

                }
                btnRGT.setOnTouchListener { _: View, event ->
                    when (event.action) {
                        MotionEvent.ACTION_DOWN -> {
                            checkBTN = 3
                            true
                        }
                        else -> {
                            checkBTN = 0
                            true
                        }
                    }

                }
                btnBWD.setOnTouchListener { _: View, event ->
                    when (event.action) {
                        MotionEvent.ACTION_DOWN -> {
                            checkBTN = 4
                            true
                        }
                        else -> {
                            checkBTN = 0
                            true
                        }
                    }

                }
            } else {
                //oast.makeText(applicationContext, "connection fail", Toast.LENGTH_SHORT).show()
                setResult(-1, intent)
                finish()
            }

            while (checkBTN != -1) {
                sock.socketSend(checkBTN.toString())
                delay(100L)
            }
        }

    }

    override fun onDestroy() {
        super.onDestroy()
        if (sock.sockCHECK() == true) {
            Log.d("디버그", "socket shut down")
            sock.sockend()
        }
        socket.cancel()
        mJob.cancel()
    }
}
