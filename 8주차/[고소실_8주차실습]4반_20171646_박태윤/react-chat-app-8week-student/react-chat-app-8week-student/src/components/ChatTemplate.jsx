import React, { useState, useRef } from "react";
import styled from "styled-components";
import MessenagerTemplate from "./MessengerTemplate";
import ChatLogTemplate from "./ChatLogTemplate";

// 전체를 감싸는 컴포넌트
function ChatTemplate() {
  	const [ chats, setChats ] = useState([])
	const nextId = useRef(0);
	// chats 배열에 채팅 추가
	const getChatLog = (username, message) => {
    	// 8주차 실습 구현
		const chat = {
			id: nextId.current,
			username,
			message,
		};
		setChats(chats.concat(chat))
		nextId.current += 1;
	}

	return (
    	<Container>
			<MessenagerTemplate getChatLog={getChatLog} />
			<ChatLogTemplate chats={chats} />
		</Container>
	);
}

const Container = styled.div`
  display: grid;
  grid-template-columns: 1fr 1fr;
  margin: 30px;
  min-height: 30rem; 
  font-size: 20px;
  position: relative; 
`;

export default ChatTemplate;