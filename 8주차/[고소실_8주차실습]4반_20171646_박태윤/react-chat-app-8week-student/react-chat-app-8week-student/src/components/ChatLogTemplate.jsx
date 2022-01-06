import React from "react";
import styled from "styled-components";

import ChatLogItem from "./ChatLogItem";
import MessengerTemplate from "./MessengerTemplate";


function ChatLogTemplate({ chats }) {

  // chats 배열을 받아 저장해 둔 채팅 로그를 보여줌
  // ChatLogItem 컴포넌트 사용
    return (
        <ChatContainer>

          <h1 style={{ color: '000000'}}>Chat Log</h1>

          {chats.map((chat) => {
              return <ChatLogItem chat={chat} username={chat.username} message={chat.message} />
          })}
      </ChatContainer>
     
  );

}

const ChatContainer = styled.div`  
  width: 700px;
  height: 600px;
  margin: 0px;
  padding: 20px;
  display: flex;
  flex-direction: column;
  background-color: #EEE8AA;
  position: relative;
  border-radius : 20px;
  box-shadow : 10px 10px 10px rgba(0,0,0,0.9);
  // 해당 영역 모서리를 둥글게
  // 해당 영역 모서리에 그림자
  // 해당 영역의 배경색 변경
  // 8주차 실습 구현
`;

export default ChatLogTemplate;