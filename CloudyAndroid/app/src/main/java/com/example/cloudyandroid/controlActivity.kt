package com.example.cloudyandroid;

import android.annotation.SuppressLint
import android.app.Activity
import android.content.Intent
import android.os.Bundle
import android.support.v7.app.AppCompatActivity
import android.util.Log
import android.widget.EditText
import android.widget.Toast
import kotlinx.android.synthetic.main.activity_control.*
import kotlinx.android.synthetic.main.activity_main.*
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.Job
import kotlinx.coroutines.launch
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
    //lateinit = 선언 이후 초기화

    override val coroutineContext: CoroutineContext
        get() = mJob + Dispatchers.Main


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_control)

        mJob = Job()
        Log.d("디버그", "control start")
        val bundle : Bundle ?= intent.extras
        //? ->> nullable

        val hostIP = InetAddress.getByName(bundle!!.getString("IP"))
        val PORT = bundle!!.getInt("PORT")



        var socket: Job

        socket = launch(Dispatchers.Default) {
            var socketC = socketClass()
            if(socketC.socketConnect(hostIP,PORT)==TRUE)
            {
                //Toast.makeText(applicationContext,"connection success",Toast.LENGTH_SHORT).show()
                //스레드가 다른 액티비티에 토스트를 띄울 때 에러 발생
            }
            else {
                //oast.makeText(applicationContext, "connection fail", Toast.LENGTH_SHORT).show()
                setResult(-1)
            }

        }
    }

    override fun onDestroy() {
        super.onDestroy()

        mJob.cancel()
    }
}
