package com.example.cloudyandroid

import android.annotation.SuppressLint
import android.app.Activity
import android.app.AlertDialog
import android.content.Intent
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.util.Log.d
import android.view.ContextThemeWrapper
import android.widget.EditText
import android.widget.Toast
import android.widget.Toast.LENGTH_LONG
import android.widget.Toast.LENGTH_SHORT
import kotlinx.android.synthetic.main.activity_main.*
import java.io.InputStream
import java.io.OutputStream
import java.lang.Exception
import java.net.InetAddress
import java.net.Socket
import kotlinx.coroutines.*
import java.util.Calendar.LONG
import kotlin.coroutines.CoroutineContext


class MainActivity : AppCompatActivity(){

    @SuppressLint("ResourceType")


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        var etIP = findViewById<EditText>(R.id.etIp)
        val PORT = 8080

        val intent = Intent(this,controlActivity::class.java)
        //호스트 주소 선언 및 임시 주소 할당 (string)
        // 포트


        //버튼 클릭 리스너
        btnCnct.setOnClickListener {

            //addr에 에딧 텍스트 값 받기
            var addr = etIP.text.toString()
            //inetAddress 형으로 받기
            var hostIP = InetAddress.getByName(addr)

            intent.putExtra("IP", hostIP)
            intent.putExtra("PORT", PORT)

            startActivityForResult(intent, 3000)

        }
    }

    override fun onActivityResult(requestCode: Int, resultCode: Int, data: Intent?) {
        super.onActivityResult(requestCode, resultCode, data)

        if(requestCode ==3000)
            if(resultCode == Activity.RESULT_CANCELED){
                val alertBuilder = AlertDialog.Builder(ContextThemeWrapper(this@MainActivity,R.style.Theme_AppCompat_Light_Dialog))

                alertBuilder.setTitle("알림")
                alertBuilder.setMessage("연결 실패")

                alertBuilder.setPositiveButton("확인"){ _, _->
                    d("alert ok","OK")
                }

                alertBuilder.show()
            }
    }

    override fun onDestroy() {
        super.onDestroy()

    }
}
