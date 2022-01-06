import React, { useState, useRef, useEffect } from "react";
import styled from "styled-components";
import TextField from "@material-ui/core/TextField";
import { width } from "../../node_modules/@material-ui/system/index";
import ChatTemplate from "./ChatTemplate";

// Sending Message 부분
function MessenagerTemplate({ getChatLog }) {
    const [MsgState, setMsgState] = useState({ message: "", username: "" })
    const ref = useRef();

  const onMsgChange = (e) => {
		setMsgState({ ...MsgState, [e.target.name]: e.target.value })
	}

  // 메시지 입력 창에서 빈 경우에는 ‘메시지를 입력하세요‘라는 내용의 경고 창 출력 후 리턴(alert 함수 사용)
  // 사용자의 이름 입력 창이 빈 경우에는 사용자 이름을 ‘이름없음’으로 저장
  // MsgState의 속성(키)들의 값을 빈 문자열로 초기화
	const onMsgSubmit = (e) => {
        e.preventDefault();
 
    // 8주차 실습 구현
        if (!MsgState) return;
        if (MsgState.message == "") {
            alert("메시지를 입력하세요");
            return;
        }
        if(MsgState.username == ""){
            MsgState.username = "이름 없음";
        }
        //getChatLog.onSubmit(MsgState);
        getChatLog(MsgState.username, MsgState.message);
        
        setMsgState({ message: "", username: "" });
	}

    return (
        <div>
            
            <Form>
                
                
            <UserName>
                
                    <TextField
                        label="User Name"
                        value={MsgState.username}
                        name="username"
                        onChange={onMsgChange}
                    />
                </UserName>


                <MessageContents>
                
                <div style = {{textAlign : 'center'}}>
                        
                        <TextField
                            label="Message"
                            value={MsgState.message}
                            name="message"
                            onChange={onMsgChange}
                            />
                </div>
            </MessageContents>

            

            <Title>
                <h1 style={{ color: '#ffffff' }}>Sending Message</h1>
            </Title>

                
            </Form>

            <Button
                type="submit"
                onClick={onMsgSubmit}
                style={{ color: '#000000' }}
            >
                SEND
          </Button>
            
        </div>
			
  );
}

// Sending Message 글씨 박스
const Title = styled.h1`
  width: 600px;
  margin: 10px;
  //padding: 1px;
  display: flex;
  flex-direction: column;
  background-color: #DAA502;
  font-size: 20px;
  position: relative;

  top : -200px;
  right : -30px;
  border-radius : 10px;
 
  
  // 해당 영역 모서리를 둥글게
  // 해당 영역의 배경색 변경
  // 해당 영역 안 텍스트 폰트색 변경
  // 8주차 실습 구현
`;

// 채팅 메시지 입력 form
const Form = styled.form`
  width: 700px;
  height: 600px;
  margin: 10px;
  padding: 20px;
  display: flex;
  flex-direction: column;
  background-color: #FFFFCC;
  position: relative;
  top: -10px;
  border-radius : 20px;
  box-shadow : 10px 10px 10px rgba(0,0,0,0.9);

  //overflow-y: scroll;
  // 해당 영역 모서리를 둥글게
  // 해당 영역 모서리에 그림자
  // 해당 영역의 배경색 변경
  // 8주차 실습 구현
`;

// username 표시
const UserName = styled.div`
  margin: 40px;
  position: relative;
  top : 200px;

`;

// 채팅 메시지 부분
const MessageContents = styled.div`
   margin: 30px;
   position: relative;
   
   font-size: 10px;
    top : 250px;
`;

// send 버튼
const Button = styled.button`
  margin-top: 60px;
  padding: 10px;
  position: relative;
  top : -150px;
  border-radius : 20px;
  border-color : red;
  border-width : 5px;
  

  // 해당 영역 모서리를 둥글게
  // 해당 영역 모서리색 변경
  // 해당 영역의 배경색 변경
  // 8주차 실습 구현
`;

export default MessenagerTemplate;