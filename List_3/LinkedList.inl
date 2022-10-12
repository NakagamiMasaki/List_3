/**
* @brief	双方向リスト実装
* @data		2022/10/06
*/

//===== インクルード =====
#include <assert.h>
#include "LinkedList.h"

//===== 関数定義 =====

//====== LinkedList::ConstIterator =====

template<class _DataType>
LinkedList<_DataType>::ConstIterator::ConstIterator(void)
	: m_pCurrentNode(nullptr)
	, m_pList(nullptr)
{
}

template<class _DataType>
typename LinkedList<_DataType>::ConstIterator& LinkedList<_DataType>::ConstIterator::operator--(void)
{
	// リストの先頭方向に1つ進む
	assert(IsValidReference() && "Invalid Reference");									// リストを参照しているか？
	assert(m_pCurrentNode->pPrev != m_pList->m_pDummy && "This Iterator Is Begin");		// 先頭ノードを既に指しているのに、さらに前に進もうとしていないか？

	m_pCurrentNode = m_pCurrentNode->pPrev;
	return *this;
}

template<class _DataType>
typename LinkedList<_DataType>::ConstIterator& LinkedList<_DataType>::ConstIterator::operator++(void)
{
	// リストの末尾方向に1つ進む
	assert(IsValidReference() && "Invalid Reference");						// リストを参照しているか？
	assert(!IsDummy() && "This Iterator Is End, Reference To DummyNode");	// ダミーノードを指しているのに、さらに進もうとしていないか？

	m_pCurrentNode = m_pCurrentNode->pNext;
	return *this;
}

template<class _DataType>
typename LinkedList<_DataType>::ConstIterator LinkedList<_DataType>::ConstIterator::operator--(int)
{
	// リストの先頭方向に1つ進む
	assert(IsValidReference() && "Invalid Reference");									// リストを参照しているか？
	assert(m_pCurrentNode->pPrev != m_pList->m_pDummy && "This Iterator Is Begin");		// 先頭ノードを既に指しているのに、さらに前に進もうとしていないか？

	LinkedList::ConstIterator TempItr = *this;	// コピーする
	m_pCurrentNode = m_pCurrentNode->pPrev;

	return TempItr;
}

template<class _DataType>
typename LinkedList<_DataType>::ConstIterator LinkedList<_DataType>::ConstIterator::operator++(int)
{
	// リストの末尾方向に1つ進む
	assert(IsValidReference() && "Invalid Reference");						// リストを参照しているか？
	assert(!IsDummy() && "This Iterator Is End, Reference To DummyNode");	// ダミーノードを指しているのに、さらに進もうとしていないか？

	LinkedList::ConstIterator TempItr = *this;	// コピーする
	m_pCurrentNode = m_pCurrentNode->pNext;

	return TempItr;
}

template<class _DataType>
const _DataType& LinkedList<_DataType>::ConstIterator::operator*(void) const
{
	// 不正なイテレータでないことを確認する
	assert(IsValidReference() && "Invalid Reference");						// 適切な参照を持つか？
	assert(!IsDummy() && "This Iterator Is End, Reference To DummyNode");	// ダミーノードを指していないか？

	return m_pCurrentNode->Data;
}

template<class _DataType>
LinkedList<_DataType>::ConstIterator::ConstIterator(const ConstIterator& ConstItr)
	: m_pCurrentNode(ConstItr.m_pCurrentNode)
	, m_pList(ConstItr.m_pList)
{
}

template<class _DataType>
typename LinkedList<_DataType>::ConstIterator& LinkedList<_DataType>::ConstIterator::operator=(const ConstIterator& Itr)
{
	this->m_pCurrentNode = Itr.m_pCurrentNode;
	this->m_pList        = Itr.m_pList;
	return *this;
}

template<class _DataType>
bool LinkedList<_DataType>::ConstIterator::operator==(const ConstIterator& Itr) const
{
	return this->m_pCurrentNode == Itr.m_pCurrentNode;
}

template<class _DataType>
bool LinkedList<_DataType>::ConstIterator::operator!=(const ConstIterator& Itr) const
{
	return !(*this == Itr);
}

template<class _DataType>
bool LinkedList<_DataType>::ConstIterator::IsValid(void) const
{
	return IsValidReference() && !IsDummy();
}

template<class _DataType>
bool LinkedList<_DataType>::ConstIterator::IsValidReference(void) const
{
	return m_pList != nullptr && m_pCurrentNode != nullptr;
}

template<class _DataType>
bool LinkedList<_DataType>::ConstIterator::IsDummy(void) const
{
	if (!IsValidReference())
		return false;

	return m_pList->m_pDummy == m_pCurrentNode;		// 参照しているリストのダミーノードと一致しているか？
}

//====== LinkedList::Iterator =====

template<class _DataType>
_DataType& LinkedList<_DataType>::Iterator::operator* (void)
{
	// 不正なイテレータでないことを確認する。
	assert(this->IsValidReference() && "Invalid Reference");						// 適切な参照を持つか？
	assert(!this->IsDummy() && "This Iterator Is End, Reference To DummyNode");	// ダミーノードを指していないか？
	return this->m_pCurrentNode->Data;
}

//===== LinkedList =====

template<class _DataType>
LinkedList<_DataType>::LinkedList(void)
	: m_ElementCount(0)
	, m_pDummy(nullptr)
{
	m_pDummy = new Node;
	m_pDummy->pNext = m_pDummy;
	m_pDummy->pPrev = m_pDummy;
}

template<class _DataType>
LinkedList<_DataType>::~LinkedList(void)
{
	Clear();

	// ダミーノードを解放する
	delete m_pDummy;
}

template<class _DataType>
size_t LinkedList<_DataType>::GetSize(void) const
{
	return m_ElementCount;
}

template<class _DataType>
bool LinkedList<_DataType>::Insert(ConstIterator& Itr, const _DataType& Data)
{
	//*** イテレータの有効性をチェック
	if (!Itr.m_pCurrentNode || Itr.m_pList != this)
		return false;

	//*** 新しい要素を渡されたイテレータの前に挿入する
	// 新しいイテレータとノードを作成する
	ConstIterator NewItr;		// 新しいイテレータ
	Node* pNode = new Node;		// 新しいノード

	// 初期化
	pNode->Data = Data;	// データを設定

	// ポインタを繋ぎなおす
	pNode->pPrev                     = Itr.m_pCurrentNode->pPrev;
	pNode->pNext                     = Itr.m_pCurrentNode;
	Itr.m_pCurrentNode->pPrev->pNext = pNode;
	Itr.m_pCurrentNode->pPrev        = pNode;

	// 要素数を更新
	++m_ElementCount;

	return true;
}

template<class _DataType>
bool LinkedList<_DataType>::Delete(ConstIterator& Itr)
{
	// 要素数のチェック
	if (m_ElementCount == 0)
		return false;

	// イテレータが不正でないことをチェック
	if (!Itr.m_pCurrentNode || Itr.m_pList != this)
		return false;

	// ダミーノードを指していないかチェック
	if (Itr.m_pCurrentNode == m_pDummy)
		return false;

	// ポインタを繋ぎなおす
	Itr.m_pCurrentNode->pPrev->pNext = Itr.m_pCurrentNode->pNext;
	Itr.m_pCurrentNode->pNext->pPrev = Itr.m_pCurrentNode->pPrev;

	// 解放
	delete Itr.m_pCurrentNode;
	Itr.m_pCurrentNode = nullptr;

	// 要素数を更新
	--m_ElementCount;

	return true;
}

template<class _DataType>
void LinkedList<_DataType>::Clear(void)
{
	// 全てのデータを削除する
	while (m_ElementCount > 0)
	{
		auto Itr = GetBegin();
		Delete(Itr);
	}
}

template<class _DataType>
typename LinkedList<_DataType>::ConstIterator LinkedList<_DataType>::GetConstBegin(void) const
{
	// 先頭のノードを指すイテレータを返す
	ConstIterator Itr;
	Itr.m_pCurrentNode = m_pDummy->pNext;
	Itr.m_pList        = this;

	return Itr;
}

template<class _DataType>
typename LinkedList<_DataType>::Iterator LinkedList<_DataType>::GetBegin(void)
{
	// 先頭のノードを指すイテレータを返す
	Iterator Itr;
	Itr.m_pCurrentNode = m_pDummy->pNext;
	Itr.m_pList        = this;

	return Itr;
}

template<class _DataType>
typename LinkedList<_DataType>::ConstIterator LinkedList<_DataType>::GetConstEnd(void) const
{
	// 常にダミーノードを指すイテレータを返す
	ConstIterator Itr;
	Itr.m_pCurrentNode = m_pDummy;
	Itr.m_pList        = this;
	return Itr;
}

template<class _DataType>
typename LinkedList<_DataType>::Iterator LinkedList<_DataType>::GetEnd(void)
{
	// 常にダミーノードを指すイテレータを返す
	Iterator Itr;
	Itr.m_pCurrentNode = m_pDummy;
	Itr.m_pList        = this;
	return Itr;
}
