package com.example.cloudyandroid;

import android.annotation.SuppressLint
import android.app.Activity
import android.content.Intent
import android.os.Build
import android.os.Bundle
import android.support.v7.app.AppCompatActivity
import android.util.Log
import android.view.MotionEvent
import android.view.View
import android.webkit.WebView
import android.webkit.WebViewClient
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
    //코루틴 소켓 루틴 추가(전역)
    //lateinit = 선언 이후 초기화
    lateinit var socket : Job
    //소켓 객체 생성
    lateinit var sock: socketClass


    //코루틴 콘텍스트 오버라이드
    override val coroutineContext: CoroutineContext
        get() = mJob + Dispatchers.Main

    //oncreate
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_control)

        mJob = Job()
        //제어 시작 확인 로그
        Log.d("디버그", "control start")

        //이전 intent로부터 extra 받아오기
        val bundle: Bundle? = intent.extras
        //? ->> nullable
        //받아온 extra로 변수 정의
        val hostIP = InetAddress.getByName(bundle!!.getString("IP"))
        val PORT = bundle!!.getInt("PORT")

        //웹 스트리밍 서버 접속 IP 포맷 작성
        var webIP = "http://" + bundle!!.getString("IP")+":8090/?action=stream/"

        //webIP = "http://192.168.0.211:8090/?action=stream/"

        //웹뷰 선언
        var wV : WebView = findViewById(R.id.webV)

        //동작
        socket = Job()

        //눌린 버튼 확인 변수
        var checkBTN = 0
        //소켓 인스턴스 객체생성
        sock = socketClass()
        //각 방향키의 리스너 할당
        btnFWD.setOnTouchListener { _: View, event ->
            //버튼에 어떤 행동이 취해졌는지
            when (event.action) {
                //눌려있는 상태일 경우
                MotionEvent.ACTION_DOWN -> {
                    Log.d("디버그","FWD-DOWN")
                    //버튼 고유 값으로 변수값 변경
                    checkBTN = 1
                    true
                }
                //떼어질 경우
                MotionEvent.ACTION_UP -> {
                    Log.d("디버그","FWD-UP")
                    checkBTN = 0
                    true
                }
                //벗어날 경우
                MotionEvent.ACTION_CANCEL ->{
                    Log.d("디버그","FWD-CANCEL")
                    //기본 값으로
                    checkBTN = 0
                    true
                }
                else -> {
                    true
                }
            }

        }

        btnLEFT.setOnTouchListener { _: View, event ->
            when (event.action) {
                MotionEvent.ACTION_DOWN -> {
                    Log.d("디버그","LEFT-DOWN")
                    checkBTN = 3
                    true
                }
                MotionEvent.ACTION_UP -> {
                    Log.d("디버그","LEFT-UP")
                    checkBTN = 0
                    true
                }
                MotionEvent.ACTION_CANCEL ->{
                    Log.d("디버그","LEFT-CANCEL")
                    checkBTN = 0
                    true
                }
                else -> {
                    true
                }
            }

        }
        btnRGT.setOnTouchListener { _: View, event ->
            when (event.action) {
                MotionEvent.ACTION_DOWN -> {
                    checkBTN = 4
                    true
                }
                MotionEvent.ACTION_UP -> {
                    Log.d("디버그","RIGHT-UP")
                    checkBTN = 0
                    true
                }
                MotionEvent.ACTION_CANCEL ->{
                    Log.d("디버그","RIGHT-CANCEL")
                    checkBTN = 0
                    true
                }
                else -> {
                    true
                }
            }

        }
        btnBWD.setOnTouchListener { _: View, event ->
            when (event.action) {
                MotionEvent.ACTION_DOWN -> {
                    checkBTN = 2
                    true
                }
                MotionEvent.ACTION_UP -> {
                    Log.d("디버그","BWD-UP")
                    checkBTN = 0
                    true
                }
                MotionEvent.ACTION_CANCEL ->{
                    Log.d("디버그","BWD-CANCEL")
                    checkBTN = 0
                    true
                }
                else -> {
                    true
                }
            }

        }

        //socket = launch(Dispatchers.Default) {
        //새로운 코루틴(쓰레드) 할당 - > socket통신을 위함
        socket = GlobalScope.launch {
            if (sock.socketConnect(hostIP, PORT) == TRUE) {
                //Toast.makeText(applicationContext,"connection success",Toast.LENGTH_SHORT).show()
                //스레드가 다른 액티비티에 토스트를 띄울 때 에러 발생
                true

            } else {
                //oast.makeText(applicationContext, "connection fail", Toast.LENGTH_SHORT).show()
                setResult(-1, intent)
                finish()
            }

            //0.1초 단위로 계속 chceck BTN 값 전송
            while (checkBTN != -1) {
                sock.socketSend(checkBTN.toString())
                Log.d("디버그","socket sending.. : " + checkBTN)
                delay(100L)
            }
        }
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.KITKAT) { WebView.setWebContentsDebuggingEnabled(true) }

        //웹뷰의 설정->현재 상황에 알맞게 설정
        wV.webViewClient = WebViewClient()
        wV.settings.javaScriptEnabled = true
        wV.settings.loadWithOverviewMode = true
        wV.settings.setUseWideViewPort(true);       // wide viewport를 사용하도록 설정
        wV.settings.setLoadWithOverviewMode(true);



        //웹뷰에 url할당
        wV.loadUrl(webIP)
    }

    override fun onDestroy() {
        super.onDestroy()
        //인텐트가 닫힐 때 소켓이 열려있는 경우 닫게함
        if (sock.sockCHECK() == true) {
            Log.d("디버그", "socket shut down")
            sock.sockend()
        }
        socket.cancel()
        mJob.cancel()
    }
}
