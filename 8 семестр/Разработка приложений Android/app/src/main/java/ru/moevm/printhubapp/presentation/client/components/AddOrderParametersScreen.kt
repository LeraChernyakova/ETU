package ru.moevm.printhubapp.presentation.client.components

import androidx.compose.foundation.BorderStroke
import androidx.compose.foundation.background
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.foundation.layout.width
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material3.Button
import androidx.compose.material3.ButtonDefaults
import androidx.compose.material3.CircularProgressIndicator
import androidx.compose.material3.DropdownMenu
import androidx.compose.material3.DropdownMenuItem
import androidx.compose.material3.HorizontalDivider
import androidx.compose.material3.Icon
import androidx.compose.material3.OutlinedTextField
import androidx.compose.material3.OutlinedTextFieldDefaults
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.collectAsState
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.layout.onGloballyPositioned
import androidx.compose.ui.platform.LocalDensity
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.res.stringResource
import androidx.compose.ui.text.TextStyle
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.lifecycle.viewmodel.compose.viewModel
import ru.moevm.printhubapp.R
import ru.moevm.printhubapp.domain.entity.Order
import ru.moevm.printhubapp.presentation.client.state.AddOrderParametersState
import ru.moevm.printhubapp.presentation.client.viewmodels.AddOrderParametersViewModel
import ru.moevm.printhubapp.ui.theme.AppTheme
import ru.moevm.printhubapp.utils.LIMIT_CHAR
import kotlin.random.Random

@Composable
fun AddOrderParametersScreen(
    onBack: () -> Unit,
    onAbout: () -> Unit,
    onNext: (format: String, paperCount: Int, comment: String, totalPrice: Int) -> Unit,
    viewModel: AddOrderParametersViewModel
) {
    val state by viewModel.state.collectAsState()

    var totalPrice by remember { mutableStateOf(0) }
    var showPriceList by remember { mutableStateOf(false) }
    var selectedDropMenu by remember { mutableStateOf(R.string.select_format_print) }
    var printFormat by remember { mutableStateOf(PrintFormatItem.A1) }
    var countList by remember { mutableStateOf(1) }
    var comment by remember { mutableStateOf("") }

    Scaffold(
        topBar = {
            Column(
                modifier = Modifier
                    .fillMaxWidth()
                    .background(AppTheme.colors.orange10)
                    .padding(top = 32.dp)
            ) {
                Row(
                    modifier = Modifier
                        .fillMaxWidth()
                        .padding(16.dp),
                    verticalAlignment = Alignment.CenterVertically,
                    horizontalArrangement = Arrangement.SpaceBetween
                ) {
                    Row(
                        verticalAlignment = Alignment.CenterVertically,
                    ) {
                        Icon(
                            modifier = Modifier.clickable { onBack() },
                            painter = painterResource(R.drawable.back_arrow_ic),
                            contentDescription = null,
                            tint = AppTheme.colors.black9
                        )
                        Spacer(modifier = Modifier.width(12.dp))
                        Text(
                            text = stringResource(R.string.add_order_title),
                            fontSize = 24.sp,
                            fontWeight = FontWeight.SemiBold,
                            color = AppTheme.colors.black9
                        )
                    }
                    Icon(
                        modifier = Modifier.clickable { onAbout() },
                        painter = painterResource(R.drawable.info_ic),
                        contentDescription = null,
                        tint = AppTheme.colors.black9
                    )
                }
                HorizontalDivider(
                    color = AppTheme.colors.black9
                )
            }
        },
    ) { paddingValues ->
        Column(
            modifier = Modifier
                .fillMaxSize()
                .padding(paddingValues)
                .padding(16.dp),
            horizontalAlignment = Alignment.CenterHorizontally,
            verticalArrangement = Arrangement.SpaceBetween
        ) {
            when (state) {
                is AddOrderParametersState.Init -> {
                    Column(
                        modifier = Modifier.fillMaxWidth(),
                        horizontalAlignment = Alignment.CenterHorizontally
                    ) {
                        ShowPrice(
                            modifier = Modifier
                                .clickable { showPriceList = true }
                                .background(AppTheme.colors.gray1, RoundedCornerShape(12.dp))
                                .padding(vertical = 8.dp, horizontal = 16.dp)
                                .align(Alignment.Start),
                        )
                        Spacer(modifier = Modifier.height(8.dp))
                        ChooseFormatPrint(
                            currentId = selectedDropMenu
                        ){ new ->
                            selectedDropMenu = new.value
                            printFormat = new
                            totalPrice = printFormat.price * countList
                        }
                        Spacer(modifier = Modifier.height(8.dp))
                        ChooseCountList(
                            currentCountList = countList
                        ) { newCount ->
                            countList = newCount
                        }
                        Spacer(modifier = Modifier.height(8.dp))
                        ChooseFile()
                        Spacer(modifier = Modifier.height(16.dp))
                        if(selectedDropMenu != R.string.select_format_print) {
                            totalPrice = printFormat.price * countList

                        }
                        Text(
                            modifier = Modifier
                                .align(Alignment.End)
                                .background(AppTheme.colors.orange3, RoundedCornerShape(16.dp))
                                .padding(vertical = 4.dp, horizontal = 8.dp),
                            text = String.format(stringResource(R.string.total_price), totalPrice),
                            fontSize = 20.sp,
                            fontWeight = FontWeight.SemiBold,
                            color = AppTheme.colors.black9
                        )
                        Spacer(modifier = Modifier.height(32.dp))
                        Comment(comment = comment, onCommentChange = { comment = it })
                    }
                    val isEnable = (selectedDropMenu != R.string.select_format_print)
                    Button(
                        onClick = {
                            onNext(
                                printFormat.name,
                                countList,
                                comment,
                                totalPrice
                            )
                        },
                        enabled = isEnable,
                        modifier = Modifier.fillMaxWidth(),
                        colors = ButtonDefaults.buttonColors(
                            containerColor = AppTheme.colors.orange10,
                            contentColor = AppTheme.colors.black9,
                            disabledContainerColor = AppTheme.colors.gray1,
                            disabledContentColor = AppTheme.colors.gray7
                        ),
                        shape = RoundedCornerShape(12.dp)
                    ) {
                        Text(
                            modifier = Modifier.padding(vertical = 8.dp),
                            text = stringResource(R.string.create_order_button_text),
                            fontSize = 20.sp,
                            fontWeight = FontWeight.Medium
                        )
                    }
                }
                is AddOrderParametersState.Loading -> {
                    Box(
                        modifier = Modifier.fillMaxSize(),
                        contentAlignment = Alignment.Center
                    ){
                        CircularProgressIndicator(
                            color = AppTheme.colors.orange10,
                        )
                    }
                }
                else -> {}
            }
        }
    }
    if(showPriceList) {
        PriceListDialog(
            onDismiss = { showPriceList = false },
        )
    }
}

@Composable
private fun ShowPrice(
    modifier: Modifier = Modifier,
) {
    Row(
        modifier = modifier,
        verticalAlignment = Alignment.CenterVertically
    ) {
        Icon(
            painter = painterResource(R.drawable.price_ic),
            contentDescription = null,
            tint = AppTheme.colors.black9
        )
        Spacer(modifier = Modifier.width(8.dp))
        Text(
            text = stringResource(R.string.show_price),
            fontSize = 16.sp,
            color = AppTheme.colors.black9
        )
    }
}

@Composable
private fun ChooseFormatPrint(
    currentId: Int,
    updateFormatPrint: (new: PrintFormatItem) -> Unit
) {
    var expanded by remember { mutableStateOf(false) }
    var buttonWidth by remember { mutableStateOf(0) }
    Box(modifier = Modifier.fillMaxWidth()) {
        Button(
            modifier = Modifier
                .fillMaxWidth()
                .onGloballyPositioned { coordinates ->
                    buttonWidth = coordinates.size.width
                },
            onClick = { expanded = true },
            shape = RoundedCornerShape(12.dp),
            colors = ButtonDefaults.buttonColors(
                containerColor = AppTheme.colors.gray1,
                contentColor = AppTheme.colors.gray7,
            ),
            border = BorderStroke(1.dp, AppTheme.colors.gray7)
        ) {
            Row(
                modifier = Modifier
                    .fillMaxWidth()
                    .padding(vertical = 8.dp),
                horizontalArrangement = Arrangement.Start,
                verticalAlignment = Alignment.CenterVertically
            ) {
                val color =
                    if (currentId == R.string.select_format_print) AppTheme.colors.gray7
                    else AppTheme.colors.black9
                Text(
                    text = stringResource(currentId),
                    fontSize = 16.sp,
                    fontWeight = FontWeight.Normal,
                    color = color
                )
                Spacer(modifier = Modifier.width(12.dp))
                Icon(
                    painter = painterResource(R.drawable.drop_down_arrow_ic),
                    contentDescription = null,
                    tint = color
                )
            }
        }
        DropdownMenu(
            modifier = Modifier
                .background(AppTheme.colors.gray1, RoundedCornerShape(12.dp))
                .width(with(LocalDensity.current) { buttonWidth.toDp() }),
            expanded = expanded,
            onDismissRequest = { expanded = false }
        ) {
            PrintFormatItem.entries.forEach {
                DropdownMenuItem(
                    text = {
                        Text(
                            text = stringResource(it.value),
                            fontSize = 16.sp,
                            fontWeight = FontWeight.Normal,
                            color = AppTheme.colors.black9
                        )
                    },
                    onClick = {
                        updateFormatPrint(it)
                        expanded = false
                    }
                )
            }
        }
    }
}

@Composable
private fun ChooseCountList(
    currentCountList: Int,
    updateCountList: (newCount: Int) -> Unit
) {
    Button(
        modifier = Modifier
            .fillMaxWidth(),
        enabled = false,
        onClick = {},
        shape = RoundedCornerShape(12.dp),
        colors = ButtonDefaults.buttonColors(
            disabledContentColor = AppTheme.colors.gray7,
            disabledContainerColor = AppTheme.colors.gray1,
        ),
        border = BorderStroke(1.dp, AppTheme.colors.gray7)
    ) {
        Row(
            modifier = Modifier
                .fillMaxWidth()
                .padding(vertical = 8.dp),
            horizontalArrangement = Arrangement.SpaceBetween,
            verticalAlignment = Alignment.CenterVertically
        ) {
            Text(
                text = stringResource(R.string.count_list),
                fontSize = 16.sp,
                fontWeight = FontWeight.Normal,
                color = AppTheme.colors.black9
            )
            Row(
                verticalAlignment = Alignment.CenterVertically
            ) {
                Icon(
                    modifier = Modifier
                        .clickable { if (currentCountList != 1)  updateCountList(currentCountList-1) },
                    painter = painterResource(R.drawable.minus_ic),
                    contentDescription = null,
                    tint = AppTheme.colors.black9
                )
                Text(
                    modifier = Modifier.padding(horizontal = 12.dp),
                    text = currentCountList.toString(),
                    fontSize = 16.sp,
                    fontWeight = FontWeight.SemiBold,
                    color = AppTheme.colors.black9
                )
                Icon(
                    modifier = Modifier
                        .size(20.dp)
                        .clickable { updateCountList(currentCountList + 1) },
                    painter = painterResource(R.drawable.add_ic),
                    contentDescription = null,
                    tint = AppTheme.colors.black9
                )
            }
        }
    }
}

@Composable
private fun ChooseFile() {
    Button(
        modifier = Modifier
            .fillMaxWidth(),
        enabled = false,
        onClick = {},
        shape = RoundedCornerShape(12.dp),
        colors = ButtonDefaults.buttonColors(
            disabledContentColor = AppTheme.colors.gray7,
            disabledContainerColor = AppTheme.colors.gray1,
        ),
        border = BorderStroke(1.dp, AppTheme.colors.gray7)
    ) {
        Row(
            modifier = Modifier
                .fillMaxWidth()
                .padding(vertical = 8.dp),
            horizontalArrangement = Arrangement.SpaceBetween,
            verticalAlignment = Alignment.CenterVertically
        ) {
            Text(
                text = stringResource(R.string.add_file),
                fontSize = 16.sp,
                fontWeight = FontWeight.Normal,
                color = AppTheme.colors.black9
            )
            Icon(
                painter = painterResource(R.drawable.add_file_ic),
                contentDescription = null,
                tint = AppTheme.colors.black9
            )
        }
    }
}

@Composable
private fun Comment(comment: String, onCommentChange: (String) -> Unit) {
    Column {
        OutlinedTextField(
            modifier = Modifier
                .fillMaxWidth()
                .height(185.dp),
            value = comment,
            onValueChange = {
                onCommentChange(if (it.length < LIMIT_CHAR) it else it.take(LIMIT_CHAR))
            },
            placeholder = {
                Text(
                    modifier = Modifier
                        .fillMaxSize()
                        .align(Alignment.Start),
                    text = stringResource(R.string.placeholder_comment),
                    fontSize = 16.sp,
                    fontWeight = FontWeight.Normal,
                    color = AppTheme.colors.gray7
                )
            },
            textStyle = TextStyle(
                fontSize = 16.sp,
                fontWeight = FontWeight.Normal,
                color = AppTheme.colors.black9
            ),
            shape = RoundedCornerShape(12.dp),
            colors = OutlinedTextFieldDefaults.colors(
                unfocusedContainerColor = AppTheme.colors.gray1,
                focusedContainerColor = AppTheme.colors.gray1,
                disabledContainerColor = AppTheme.colors.gray1,
                disabledBorderColor = AppTheme.colors.gray7,
                unfocusedBorderColor = AppTheme.colors.gray7,
                focusedBorderColor = AppTheme.colors.gray7
            )
        )
        Spacer(modifier = Modifier.height(4.dp))
        Text(
            modifier = Modifier.align(Alignment.End),
            text = "${comment.length} / $LIMIT_CHAR",
            fontSize = 14.sp,
            color = AppTheme.colors.gray7
        )
    }
}

@Preview(showBackground = true)
@Composable
private fun AddOrderParametersScreenPreview() {
    AddOrderParametersScreen(
        onBack = {},
        onAbout = {},
        onNext = { _, _, _, _ -> },
        viewModel = viewModel()
    )
}