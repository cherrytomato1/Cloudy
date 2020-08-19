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

    //소켓 통신용 포트 설정
    val PORT = 8080

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        //버튼 클릭 리스너
        btnCnct.setOnClickListener {
            //새 인텐트 call 함수
            call_Activity()
        }
    }



    fun call_Activity(){
        //새 인텐트 정의
        val controlIntent= Intent(this,controlActivity::class.java)
        //사용할 IP가 적힌 edittext 정의
        var etIP =findViewById<EditText>(R.id.etIp)

        //addr에 에딧 텍스트 값 받기
        var addr = etIP.text.toString()
        //inetAddress 형으로 받기

        //intent로 IP, PORT 넘김
        controlIntent.putExtra("IP", addr)
        controlIntent.putExtra("PORT", PORT)
        //Intent 시작
        startActivityForResult(controlIntent, 3000)
    }
    //인텐트 리턴 함수
    override fun onActivityResult(requestCode: Int, resultCode: Int, data: Intent?) {
        super.onActivityResult(requestCode, resultCode, data)

        if(requestCode == 3000) {
            //오류일 경우
            if (resultCode == -1) {
                val alertBuilder =
                    AlertDialog.Builder(ContextThemeWrapper(this@MainActivity, R.style.Theme_AppCompat_Light_Dialog))
                //연결실패 박스 띄움
                alertBuilder.setTitle("알림")
                alertBuilder.setMessage("연결 실패")

                alertBuilder.setPositiveButton("확인") { _, _ ->
                    d("디버그", "alertOK")
                }

                alertBuilder.show()
            }

        }

    }

    override fun onDestroy() {
        super.onDestroy()

    }
}
