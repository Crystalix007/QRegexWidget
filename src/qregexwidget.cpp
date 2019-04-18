#include "qregexwidget.h"
#include "ui_qregexwidget.h"

#include <jpcre2.hpp>
#include <QPlainTextEdit>

#include <QRegularExpression>

QRegexWidget::QRegexWidget(QWidget *parent) :
		QMainWindow(parent),
		ui(new Ui::QRegexWidget)
{
	ui->setupUi(this);
	connect(ui->matchButton, &QPushButton::clicked, this, &QRegexWidget::doMatch);
}

QRegexWidget::~QRegexWidget()
{
	delete ui;
}

void QRegexWidget::doMatch()
{
	if (ui->matchRegex->text().isEmpty())
	{
		ui->statusLabel->setText("Cannot use empty match");
		return;
	}

	using jp = jpcre2::select<char>;

	const auto reOptions = this->ui->searchOptions->text().toStdString();

	jp::Regex re{ ui->matchRegex->text().toStdString(), reOptions };

	if (!re)
	{
		ui->statusLabel->setText("Invalid Regex");
		return;
	}

	std::string text{ ui->inputText->toPlainText().toStdString() };
	jp::VecNum vecNum{};
	jp::VecNas vecNas{};
	jp::VecNtN vecNtN{};
	jpcre2::VecOff matchOff{};
	jpcre2::VecOff matchEndOff{};
	jp::RegexMatch match{};

	match.setRegexObject(&re)
		.setSubject(&text)
		.setNumberedSubstringVector(&vecNum)
		.setNamedSubstringVector(&vecNas)
		.setNameToNumberMapVector(&vecNtN)
		.setMatchStartOffsetVector(&matchOff)
		.setMatchEndOffsetVector(&matchEndOff)
		.setModifier(reOptions);

	size_t count = match.match();

	ui->statusLabel->setText(QString::number(count) + " match" + (count == 1 ? "" : "es"));

	QString html{};
	size_t currPos = 0;

	for (size_t i = 0; i < matchOff.size(); i++)
	{
		html += QString::fromStdString(text.substr(currPos, matchOff[i] - currPos)).toHtmlEscaped();
		html += "<font color=\"#77f\">" + QString::fromStdString(text.substr(matchOff[i], matchEndOff[i] - matchOff[i])).toHtmlEscaped() + "</font>";
		currPos = matchEndOff[i];
	}

	html += QString::fromStdString(text.substr(currPos)).toHtmlEscaped();
	html.replace(QRegularExpression{ QString{ "\r?\n" } }, "<br />\n");

	ui->matchedText->setHtml(html);

	jp::RegexReplace rr{ &re };
	rr.setSubject(text).setReplaceWith(ui->replaceRegex->text().toStdString()).setModifier(reOptions);

	QString replaced = QString::fromStdString(rr.replace());
	ui->replacedText->setPlainText(replaced);
}
