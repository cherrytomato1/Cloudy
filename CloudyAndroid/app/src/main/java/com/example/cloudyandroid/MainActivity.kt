package com.example.cloudyandroid

import android.annotation.SuppressLint
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.widget.EditText
import android.widget.Toast
import kotlinx.android.synthetic.main.activity_main.*
import java.io.InputStream
import java.io.OutputStream
import java.lang.Exception
import java.net.InetAddress
import java.net.Socket


class MainActivity : AppCompatActivity() {

    @SuppressLint("ResourceType")
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        var Msg = findViewById(R.id.etMsg) as EditText
        var etIP = findViewById<EditText>(R.id.etIp)
        var sendMsg = "t".toByteArray()

        //호스트 주소 선언 및 임시 주소 할당 (string)
        var addr ="172.16.106.95"
        // 포트
        val PORT = 8800

        //버튼 클릭 리스너
        btnSend.setOnClickListener {

            //hostIP = Integer.parseInt(etIP.text.toString())

            //addr에 에딧 텍스트 값 받기
            addr  = etIP.text.toString()

            //inetAddress 형으로 받기
            var hostIP = InetAddress.getByName(addr)



            try{
                val sock : Socket = Socket(hostIP,PORT)

                val outStream : OutputStream = sock.getOutputStream()
                val inStream : InputStream = sock.getInputStream()

                Toast.makeText(this,addr,Toast.LENGTH_LONG).show()

                outStream.write(sendMsg)

                sock.close()
            }
            catch (e:Exception){

            }


        }
    }
}
