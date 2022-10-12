/**
* @brief	双方向リスト テンプレート化 課題
* @data		2022/10/06
*/

//===== インクルード =====
#include <iostream>
#include <fstream>
#include "LinkedList.h"
#include "ScoreData.h"

/**
* @fn		main(void)
* @brief	エントリーポイント
* @return	成功時 : 0 | 失敗時 : 0以外
*/
int main(void)
{
	//*** 変数宣言
	LinkedList<ScoreData> List;

	//*** ファイル読み込み
	std::ifstream File;
	File.open("Scores.txt");
	if (!File.is_open())
	{
		// エラーメッセージ表示 & 待機
		std::cout << "Scores.txtの読み込みに失敗しました。お手数ですが、exeファイルと同階層にファイルがあるかお確かめください。" << std::endl;
		std::cout << "終了するにはエンターキーを押してください。" << std::endl;
		std::cin.sync();
		std::cin.get();

		return -1;
	}

	//*** 1行ずつ読み込んでいく
	std::string LoadedText;
	while (std::getline(File, LoadedText))
	{
		std::string Score;	// スコア
		std::string Name;	// 名前

		// タブでスコアとユーザー名を区切る
		auto TabPos = LoadedText.find('\t');		// タブがある位置
		Score.assign(LoadedText, 0, TabPos);		// タブの前までコピー
		Name.assign(LoadedText, TabPos + 1, std::string::npos);	// タブの後ろから最後までコピー

		// リストに追加
		ScoreData Data{ std::stoi(Score), Name };
		auto Itr = List.GetEnd();
		List.Insert(Itr, Data);
	}

	//*** 中身を全て表示
	for (auto Itr = List.GetConstBegin(); Itr != List.GetConstEnd(); ++Itr)
	{
		auto& Data = *Itr;
		std::cout << Data.Score << "\t" << Data.Name << std::endl;
	}

	// 待機
	std::cout << std::endl;
	std::cout << "終了するにはエンターキーを押してください。" << std::endl;
	std::cin.sync();
	std::cin.get();

	return 0;
}