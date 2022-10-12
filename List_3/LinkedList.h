/**
* @brief	双方向リスト定義
* @data		2022/10/06
*/

#pragma once

//===== クラス定義 =====
/**
* @brief	双方向リスト
* @tparam	_DataType リストに格納したいデータ
*/
template<class _DataType>
class LinkedList
{
	//=== 構造体定義
private:

	/**
	* @brief	双方向リストのノード
	*/
	struct Node
	{
		Node* pPrev;		// 前ノードへのポインタ
		Node* pNext;		// 次ノードへのポインタ

		_DataType	Data;	// データ
	};

	//=== クラス定義
public:

	/**
	* @brief	双方向リストのコンストイテレータ
	*/
	class ConstIterator
	{
		//=== メンバ変数
	protected:

		LinkedList::Node* m_pCurrentNode;		// このイテレータが現在参照しているノード
		const LinkedList* m_pList;			// どのリストのイテレータか判別できるように

		//=== メンバ関数
	public:

		/**
		* @brief	デフォルトコンストラクタ
		*/
		ConstIterator(void);

		/**
		* @brief	リストの先頭に向かって1つ進む(前置デクリメント)
		*/
		ConstIterator& operator--(void);

		/**
		* @brief	リストの末尾に向かって1つ進む(前置インクリメント)
		*/
		ConstIterator& operator++(void);

		/**
		* @brief	リストの先頭に向かって1つ進む(後置デクリメント)
		*/
		ConstIterator operator--(int);

		/**
		* @brief	リストの末尾に向かって1つ進む(後置インクリメント)
		*/
		ConstIterator operator++(int);

		/**
		* @brief	イテレータが指す要素を取得する(コンスト版)
		*/
		const _DataType& operator*(void) const;

		/**
		* @brief	イテレータのコピーを行う(コピーコンストラクタ)
		*/
		ConstIterator(const ConstIterator& ConstItr);

		/**
		* @brief	イテレータのコピー代入を行う
		* @return	このイテレータへの左辺値参照
		*/
		ConstIterator& operator=(const ConstIterator& Itr);

		/**
		* @brief	このイテレータと同一か比較する
		* @return	同一なら true , 異なるなら false
		*/
		bool operator==(const ConstIterator& Itr) const;

		/**
		* @brief	このイテレータと異なるか比較する
		* @return	異なるなら true , 同一なら false
		*/
		bool operator!=(const ConstIterator& Itr) const;

		/**
		* @brief	不正なイテレータでないことをチェックする。
		* @details	trueが返った場合、このイテレータを介してデータにアクセスできることを保証する。
		*			(リストからこのイテレータが指している要素が削除されていない限り)
		* @return	不正でないなら true | 不正なイテレータなら false
		*/
		bool IsValid(void) const;

		/**
		* @brief	このイテレータが適切な参照を持っているかチェックする
		* @return	適切に設定されていれば true | 不正な参照なら false
		*/
		bool IsValidReference(void) const;

	protected:

		/**
		* @brief	このイテレータがダミーノードを指しているかチェックする。
		* @return	ダミーノードを指していれば true | 指していなければ false
		*/
		bool IsDummy(void) const;

		friend LinkedList;
	};

	/**
	* @brief	双方向リストの非コンストイテレータ
	*/
	class Iterator : public LinkedList<_DataType>::ConstIterator
	{
		//=== メンバ関数
	public:

		/**
		* @brief	イテレータが指す要素を取得する(非コンスト版)
		*/
		_DataType& operator*(void);
	};

	//=== メンバ変数
private:

	size_t	m_ElementCount;	// 要素数
	Node*	m_pDummy;		// ダミーノード(Prevに末尾ノード、Nextに先頭ノード)

	//=== メンバ関数
public:

	/**
	* @brief	デフォルトコンストラクタ
	*/
	LinkedList(void);

	/**
	* @brief	コピーコンストラクタ
	* @note		意図しないコピーを防ぐため、delete宣言しています。
	*/
	LinkedList(const LinkedList<_DataType>& List) = delete;

	/**
	* @brief	ムーブコンストラクタ
	* @note		意図しないムーブを防ぐため、delete宣言しています。
	*/
	LinkedList(LinkedList<_DataType>&& List) = delete;

	/**
	* @brief	デストラクタ
	*/
	virtual ~LinkedList(void);

	/**
	* @brief	データ数の取得
	*/
	size_t GetSize(void) const;

	/**
	* @brief		データの挿入
	* @param[in]	Itr		挿入したい位置
	* @param[in]	Data	新しく挿入したいデータ
	* @return		成功時 : true | 失敗時 : false
	*/
	bool Insert(ConstIterator& Itr, const _DataType& Data);

	/**
	* @brief		データの削除
	* @param[in]	Itr		削除したいデータ
	* @return		成功時 : true | 失敗時 : false
	*/
	bool Delete(ConstIterator& Itr);

	/**
	* @brief		全てのデータの削除
	*/
	void Clear(void);

	/**
	* @brief	先頭のコンストなイテレータを取得
	* @return	先頭のコンストなイテレータ
	*/
	ConstIterator GetConstBegin(void) const;

	/**
	* @brief	先頭のイテレータを取得
	* @return	先頭のイテレータ
	*/
	Iterator GetBegin(void);

	/**
	* @brief	末尾のコンストなイテレータを取得
	* @return	末尾のコンストなイテレータ
	*/
	ConstIterator GetConstEnd(void) const;

	/**
	* @brief	末尾のイテレータを取得
	* @return	末尾のイテレータ
	*/
	Iterator GetEnd(void);

	friend ConstIterator;
	friend Iterator;
};

//===== インクルード =====
#include "LinkedList.inl"
