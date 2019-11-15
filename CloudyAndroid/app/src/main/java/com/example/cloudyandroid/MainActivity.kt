package com.example.cloudyandroid

import android.annotation.SuppressLint
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.widget.EditText
import android.widget.Toast
import kotlinx.android.synthetic.main.activity_main.*
import java.net.Socket


class MainActivity : AppCompatActivity() {

    @SuppressLint("ResourceType")
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        var Msg = findViewById(R.id.etMsg) as EditText
        var etIP = findViewById<EditText>(R.id.etIp)
        var sendMsg = "t".toByteArray()

        var hostIP ="test"
        val PORT = 8800

        btnSend.setOnClickListener {


            //hostIP = Integer.parseInt(etIP.text.toString())

            hostIP = etIP.text.toString()


            Toast.makeText(this,hostIP,Toast.LENGTH_LONG).show()
            val sock = Socket(hostIP,PORT)

            val outStream = sock.getOutputStream()
            val inStream = sock.getInputStream()

            


        }
    }
}
