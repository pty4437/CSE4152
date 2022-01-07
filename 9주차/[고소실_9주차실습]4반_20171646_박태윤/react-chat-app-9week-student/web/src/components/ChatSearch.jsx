// 채팅 키워드 검색창 & 검색 버튼에 대한 컴포넌트 작성

import React, { useState } from "react";
import styled from "styled-components";
import TextField from "@material-ui/core/TextField";
import ChatLogItem from "./ChatLogItem";

// chats 배열을 받아 배열 안 각 chat 객체를 리스트로 보여 줌
function ChatSearch({ chats, onSearchKeySubmit }) {
    const [keyword, funcKey] = useState("");

    return (
            <SearchKey>
                <TextField
                    name="keyword"
                    value={keyword}
                    id="outlined-multiline-static"
                    variant="outlined"
                    label="Keyword"
                    onChange={(e) => funcKey(e.target.value)}
                />
            <SearchButton onClick={(e) => onSearchKeySubmit(keyword)}>
                Search
            </SearchButton>

            </SearchKey>

    );

}


const SearchKey = styled.div`
  margin: 30px;
`;

const SearchButton = styled.button`
  margin-top: 3px;
  margin-right: 10px;
  padding: 10px;
  height: 50px;
  background-color: white;
  border-color: #c8a951;
  border-radius: 5px;
  position:relative;
  right: -80px;
`;

export default ChatSearch;