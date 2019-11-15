package com.example.cloudyandroid

import android.annotation.SuppressLint
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.widget.EditText
import android.widget.Toast
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {

    @SuppressLint("ResourceType")
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        var etMsg = findViewById(R.id.etMsg) as EditText
        var etIp = findViewById<EditText>(R.id.etIp)
        var sendMsg = "temp".toByteArray()

        var hostIP : Int
        val PORT = 8800


        btnSend.setOnClickListener {
            Toast.makeText(this,etMsg.text,Toast.LENGTH_LONG).show()
        }
    }
}
