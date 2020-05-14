
SonarTest
---

Sonar Sensor(초음파 센서)는 초음파를 발생시키고 벽에 반사된 초음파를 수신하는 시간을 재는 센서입니다.  
초음파 센서에는 각각 좌측 __트리거(Trigger)__
와 우측 
__에코(Echo)__
가 있습니다. 트리거는 초음파를 발생시킵니다. 
초음파 신호는 물체에 닿으면 반사하는 성질이 있기 때문에 에코에서 반사된 초음파를 수신하여 초음파를 발생시킨 시점부터 수신된 시점까지의 시간을 측정할 수
있습니다.  


따라서 우리는 초음파 신호로 로봇 앞에 장애물의 유무나 
`거리 = 시간 X 속력`의 공식에 의해 거리까지 측정할 수 있습니다. 
이 때 고려해야 할 것은, 초음파의 속력은 공기중에서 **340m/s**이라는 것과 초음파 센서가 측정한 시간은 편도 이동시간이 아닌 왕복 이동시간이라는 것입니다. 
즉, 거리를 측정하기 위해서는 트리거에서 발생시킨 신호가 에코에서 수신된 시간을 측정하여 2로 나누고, 속력인 340m/s를 곱하면 됩니다.  

***

이 코드로 초음파 센서로 거리를 측정할 수 있습니다. 

코드를 업로드 하고 초음파 센서로 측정된 거리를 시리얼 모니터로 확인할 수 있습니다.